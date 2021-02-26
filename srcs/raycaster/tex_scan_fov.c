/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_scan_fov.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/26 16:35:19 by jnivala          ###   ########.fr       */
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

float			vec2_ang_offset(t_xy a, t_xy b, int offset)
{
	return acosf(vec2_dot(a, b) / (vec2_mag(a) * vec2_mag(b)));
}

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

static float	perspective_fix(int offset, float wall_len)
{
	int		i;
	int		side;
	float	sqrt2;
	float	euc_offset;
	float	new_wall_len;

	i = 0;
	new_wall_len = 0.0f;
	side = offset < 320 ? 0 : 1;
	euc_offset = offset < 320 ? offset : offset - 320;
	sqrt2 = 1.414213562f - euc_offset * 0.001294417f;
	while (i < wall_len && side == 0 && sqrt2 > 1)
	{
		new_wall_len += sqrt2;
		sqrt2 = sqrt2 - 0.001294417f;
		if (sqrt2 <= 1.0f)
		{
			sqrt2 = 1.0f;
			side = 1;
		}
		i++;
	}
	while (i < wall_len && side == 1)
	{
		new_wall_len += sqrt2;
		sqrt2 = sqrt2 - 0.001294417f;
		i++;
	}
	return (new_wall_len);
}

int				tex_ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, t_texture *tex, t_home *home, t_player *plr)
{
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		z_step;
	float		angle_mult;
	int			new_wall_len;
	int			i;

	i = 0;
	//new_wall_len = perspective_fix(SCREEN_WIDTH - frame->offset, wall_len);
	z_step = get_distance(plr->pos, left) / get_distance(plr->pos, right);
	screen_offset = SCREEN_WIDTH - frame->offset;
	wall_height_left = 480 / (fabs(left.x + left.y) * SQR2) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y) * SQR2) * 20;
	step = (wall_height_left - wall_height_right) / wall_len;
	angle_mult = angle_offset(screen_offset, wall_len);
	while (i < new_wall_len)
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
	draw_text(home, ft_itoa(new_wall_len), frame, vec2(screen_offset + (wall_len * 0.5), 240));
	return(wall_len + 1);
}

static float	round_angle(float angle, float *pxl_offset, int offset)
{
	float			angle_as_pixels;
	int				trunc;
	float			min;
	float			max;
	float			step;
	float			new_angle;

	angle_as_pixels = angle / 0.002454369f;
	max = ft_map(320 - offset, (t_range){0, 320}, (t_range){0.8, 1.2});
	min = ft_map(320 - offset + angle_as_pixels, (t_range){0, 320}, (t_range){0.8, 1.2});
	new_angle = (max - (1 - min)) * angle;
	angle_as_pixels = new_angle / 0.002454369f;
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
	float		angle;

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
		angle = vec2_angle(frame->left.left_point, frame->left.right_point);
		current_pxl = round_angle(angle, &frame->pxl_offset, SCREEN_WIDTH - frame->offset);
		//current_pxl = round_angle(vec2_angle(frame->left.left_point, frame->left.right_point), &frame->pxl_offset, vec2_angle(frame->left.left_point, vec2(PLR_DIR, PLR_DIR)));
		if (check_if_portal(frame->left.wall) && !check_if_same_point(current_pxl, &frame->left))
		{
			current_pxl++;
			draw_text(home, ft_itoa(current_pxl), frame, vec2(SCREEN_WIDTH - frame->offset + (current_pxl * 0.5), 240));
			setup_frame(frame, &new_frame, current_pxl, frame->left.wall->idx);
			tex_scan_fov(home, &new_frame, plr);
			frame->offset = new_frame.offset;
			frame->pxl_offset = new_frame.pxl_offset;
		}
		else
		{
			current_pxl = tex_ft_draw_wall(frame->left.left_point, frame->left.right_point, frame, current_pxl, get_texture(frame->left.wall->idx, home->editor_textures), home, plr);
			ft_draw_line(
				vec2_add(frame->left.left_point, home->offset),
				vec2_add(frame->left.right_point, home->offset),
				green,
				frame->draw_surf);
			frame->offset = frame->offset - current_pxl;
		}
	}
}
