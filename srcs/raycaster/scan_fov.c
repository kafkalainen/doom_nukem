/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/02 10:04:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

int				draw_tex_line(t_xy start, t_xy end, 
								t_texture *tex, SDL_Surface *surf)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	t_xy	pos;

	length = vec2(fabs(end.x - start.x), fabs(end.y - start.y));
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos.x = start.x;
	pos.y = start.y;
	while (pixels-- > 0)
	{
		if (pos.x >= 0 && pos.x < SCREEN_WIDTH && 
			pos.y >= 0 && pos.y < SCREEN_HEIGHT)
			put_pixel(surf, pos.x, pos.y, get_texel(pos.x, pos.y, tex));
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}

void			draw_wall(t_frame *frame, t_texture *tex, 
							t_home *home, t_player *plr)
{
	float		step;
	float		z_step;

	ft_calc_distances(frame);
	z_step = get_distance(plr->pos, frame->left.l_pt) / 
				get_distance(plr->pos, frame->left.l_pt);
	step = (frame->wall_h_l - frame->wall_h_r) / frame->wall_len;
	while (frame->wall_x1 < frame->wall_x2)
	{
		draw_tex_line(
			vec2(frame->wall_x1, plr->pitch - frame->wall_h_l),
			vec2(frame->wall_x1, plr->pitch + frame->wall_h_l),
			tex,
			frame->draw_surf);
		frame->wall_h_l = frame->wall_h_l - step;
		z_step -= frame->wall_len * z_step;
		frame->wall_x1 = frame->wall_x1 + 1.0f;
	}
	draw_text(home, ft_ftoa(frame->wall_len, 9, 1), frame, vec2(frame->wall_x2 - frame->wall_len * 0.5, 240));
}

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
		return ((float)(trunc + 1.0f));
	}
	else
		return ((float)trunc);
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
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			draw_wall(frame, get_tex(frame->left.wall->idx, home->editor_tex), home, plr);
			frame->offset = frame->offset - ++current_pxl;
		}
	}
}
