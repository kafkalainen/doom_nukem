/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_scan_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/02 10:04:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

float			angle_offset(float screen_offset, int screen_wall)
{
	float		angle_mult_left;
	float		angle_mult_right;
	float		euc_offset;

	euc_offset = screen_offset >= 320 ? screen_offset - 320 : screen_offset;
	angle_mult_left = FOV - euc_offset * .00178373853125f;
	angle_mult_right = FOV - (euc_offset + screen_wall) * .00178373853125f;
	return ((angle_mult_left - angle_mult_right) / screen_wall);
}

int				tex_ft_draw_line(t_xy start, t_xy end, t_texture *tex, SDL_Surface *surf)
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
		if (pos.x >= 0 && pos.x < SCREEN_WIDTH && pos.y >= 0 && pos.y < SCREEN_HEIGHT)
			put_pixel(surf, pos.x, pos.y, get_texel(pos.x, pos.y, tex));
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}

void			tex_ft_draw_wall(t_frame *frame, t_texture *tex, t_home *home, t_player *plr)
{
	float		step;
	float		z_step;

	z_step = get_distance(plr->pos, frame->left.left_point) / get_distance(plr->pos, frame->left.left_point);
	step = (frame->wall_height_left - frame->wall_height_right) / frame->wall_len;
	while (frame->wall_x1 < frame->wall_x2)
	{
		tex_ft_draw_line(
			vec2(frame->wall_x1, plr->pitch - frame->wall_height_left),
			vec2(frame->wall_x1, plr->pitch + frame->wall_height_left),
			tex,
			frame->draw_surf);
		frame->wall_height_left = frame->wall_height_left - step;
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

t_texture		*get_texture(int idx, t_texture	**textures)
{
	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	return (textures[abs(idx)]);

}

void			tex_scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame		new_frame;
	int			current_pxl;

	current_pxl = 0;
	frame->left.wall = home->sectors[frame->idx]->points;
	frame->right.wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	get_left_point(frame->left.wall, &frame->left, frame, home->sectors[frame->idx]->nb_of_walls);
	get_right_point(frame->left.wall, &frame->right, frame, home->sectors[frame->idx]->nb_of_walls);
	while (frame->offset > frame->max_fov)
	{
		if (current_pxl != 0)
			continue_from_next_point(&frame->left);
		if (check_if_same_wall(frame->left.wall->x0, frame->right.wall->x0, frame->right.right_point))
			frame->left.right_point = frame->right.right_point;
		current_pxl = round_angle(vec2_angle(frame->left.left_point, frame->left.right_point), &frame->pxl_offset);
		if (check_if_portal(frame->left.wall) && !check_if_same_point(current_pxl, &frame->left))
		{
			current_pxl++;
			setup_frame(frame, &new_frame, current_pxl, frame->left.wall->idx);
			tex_scan_fov(home, &new_frame, plr);
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			ft_calc_distances(frame);
			tex_ft_draw_wall(frame, get_texture(frame->left.wall->idx, home->editor_textures), home, plr);
			frame->offset = frame->offset - ++current_pxl;
		}
	}
}
