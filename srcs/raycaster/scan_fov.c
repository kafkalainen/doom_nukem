/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:59:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 13:50:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static float	round_angle(float angle, float *pxl_offset)
{
	float			angle_as_pixels;
	int				trunc;

	angle_as_pixels = angle / 0.002454369f;
	trunc = (int)angle_as_pixels;
	*pxl_offset = angle_as_pixels - trunc + *pxl_offset;
	if (*pxl_offset >= 1.0f)
	{
		*pxl_offset = *pxl_offset - 1.0f;
		return ((int)(trunc + 1));
	}
	else
		return ((int)trunc);
}

t_texture		*get_tex(int idx, t_texture	**textures)
{
	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	return (textures[abs(idx)]);

}

void			scan_fov(t_home *home, t_frame *frame, t_player *plr, int current_pxl)
{
	t_frame		new_frame;

	frame->left.wall = home->sectors[frame->idx]->points;
	frame->right.wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	// calc_sector_texels(home->sectors[frame->idx]);
	while (frame->offset > frame->max_fov)
	{
		get_wall_pts(frame, home->sectors[frame->idx]->nb_of_walls, current_pxl);
		current_pxl = round_angle(vec2_ang(frame->left.l_pt, frame->left.r_pt),
					&frame->pxl_offset);
		if (check_if_portal(frame->left.wall) &&
			!check_if_same_pt(current_pxl, &frame->left))
		{
			current_pxl++;
			setup_frame(frame, &new_frame, current_pxl, frame->left.wall->idx);
			scan_fov(home, &new_frame, plr, 0);
			// draw_segment(frame, home, plr);
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			draw_segment(frame, home, plr);
			frame->offset = frame->offset - ++current_pxl;
		}
	}
}
