/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/24 10:45:52 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

void		ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, int color, t_home *home, t_player *plr)
{
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		z_step;
	float		angle_mult;
	int			i;

	i = 0;
	z_step = get_distance(plr->pos, left) / get_distance(plr->pos, right);
	screen_offset = SCREEN_WIDTH - frame->offset;
	wall_height_left = 480 / (fabs(left.x + left.y) * SQR2) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y) * SQR2) * 20;
	step = (wall_height_left - wall_height_right) / wall_len;
	angle_mult = angle_offset(screen_offset, wall_len);
	while (i < wall_len)
	{
		ft_draw_line(
			vec2(screen_offset + i, plr->pitch - wall_height_left),
			vec2(screen_offset + i, plr->pitch + wall_height_left),
			color,
			frame->draw_surf);
		wall_height_left = wall_height_left - step + angle_mult;
		z_step -= wall_len * z_step;
		i++;
	}
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

void		tex_ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, t_texture *tex, t_home *home, t_player *plr)
{
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		z_step;
	float		angle_mult;
	int			i;

	i = 0;
	z_step = get_distance(plr->pos, left) / get_distance(plr->pos, right);
	screen_offset = SCREEN_WIDTH - frame->offset;
	wall_height_left = 480 / (fabs(left.x + left.y) * SQR2) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y) * SQR2) * 20;
	step = (wall_height_left - wall_height_right) / wall_len;
	angle_mult = angle_offset(screen_offset, wall_len);
	while (i < wall_len)
	{
		tex_ft_draw_line(
			vec2(screen_offset + i, plr->pitch - wall_height_left),
			vec2(screen_offset + i, plr->pitch + wall_height_left),
			tex,
			frame->draw_surf);
		wall_height_left = wall_height_left - step + angle_mult;
		z_step -= wall_len * z_step;
		i++;
	}
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
	return (textures[abs(idx)]);
}

void			tex_scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_ray_fov	fov_left;
	t_ray_fov	fov_right;
	t_frame		new_frame;
	int			current_pxl;

	current_pxl = 0;
	fov_left.left_point = vec2(-1,-1);
	fov_right.right_point = vec2(-1,-1);
	fov_left.wall = home->sectors[frame->idx]->points;
	fov_right.wall = home->sectors[frame->idx]->points;
	continue_from_last_sector(fov_left.wall, &fov_left, frame);
	get_left_point(fov_left.wall, &fov_left, frame, home->sectors[frame->idx]->nb_of_walls);
	get_right_point(fov_left.wall, &fov_right, frame, home->sectors[frame->idx]->nb_of_walls);
	draw_text(home, ft_ftoa(plr->z, 2, 1), frame, vec2(32, 32));
	while (frame->offset > frame->max_fov)
	{
		if (current_pxl != 0)
			continue_from_next_point(&fov_left);
		if (check_if_same_wall(fov_left.wall->x0, fov_right.wall->x0, fov_right.right_point))
			fov_left.right_point = fov_right.right_point;
		current_pxl = round_angle(vec2_angle(fov_left.left_point, fov_left.right_point), &frame->pxl_offset);
		if (check_if_portal(fov_left.wall) && !check_if_same_point(current_pxl, &fov_left))
		{
			current_pxl++;
			setup_frame(frame, &new_frame, current_pxl, fov_left.wall->idx);
			tex_scan_fov(home, &new_frame, plr);
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			tex_ft_draw_wall(fov_left.left_point, fov_left.right_point, frame, current_pxl, get_texture(fov_left.wall->idx, home->editor_textures), home, plr);
			ft_draw_line(
				vec2_add(fov_left.left_point, home->offset),
				vec2_add(fov_left.right_point, home->offset),
				green,
				frame->draw_surf);
			current_pxl++;
			frame->offset = frame->offset - current_pxl;
		}
	}
}
