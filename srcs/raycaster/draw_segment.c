/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/12 16:25:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		debug_wall(t_home *home, t_frame *frame)
{
	if (frame->left.wall->c == 'b')
	{
		// draw_text(home, "LEFT", frame, vec2(frame->wall_x1, 220));
		// draw_text(home, ft_ftoa(frame->wall_x1, 2, 1), frame,
		// 	vec2(frame->wall_x1, 240));
		// draw_text(home, "LEFT_PT: X and Y", frame, vec2(20, 260));
		// draw_text(home, ft_ftoa(frame->left.l_pt.x, 2, 1), frame,
		// 	vec2(frame->wall_x1, 280));
		// draw_text(home, ft_ftoa(frame->left.l_pt.y, 2, 1), frame,
		// 	vec2(frame->wall_x1, 300));
		// draw_text(home, "FULL_LEN_LEFT_PT: X and Y", frame, vec2(20, 320));
		// draw_text(home, ft_ftoa(frame->left.wall->x0.x, 2, 1), frame,
		// 	vec2(frame->wall_x1, 340));
		// draw_text(home, ft_ftoa(frame->left.wall->x0.y, 2, 1), frame,
		// 	vec2(frame->wall_x1, 360));
		// draw_text(home, "RIGHT", frame, vec2(frame->wall_x2 * 0.75, 220));
		// draw_text(home, ft_ftoa(frame->wall_x2, 2, 1), frame,
		// 	vec2(frame->wall_x2, 240));
		// draw_text(home, "RIGHT_PT: X and Y", frame,
		// 	vec2(frame->wall_x2 * 0.75, 260));
		// draw_text(home, ft_ftoa(frame->left.r_pt.x, 2, 1), frame,
		// 	vec2(frame->wall_x2, 280));
		// draw_text(home, ft_ftoa(frame->left.r_pt.y, 2, 1), frame,
		// 	vec2(frame->wall_x2, 300));
		// draw_text(home, "FULL_LEN_RIGHT_PT: X and Y", frame,
		// 	vec2(frame->wall_x2, 320));
		// draw_text(home, ft_ftoa(frame->left.wall->next->x0.x, 2, 1), frame,
		// 	vec2(frame->wall_x2, 340));
		// draw_text(home, ft_ftoa(frame->left.wall->next->x0.y, 2, 1), frame,
		// 	vec2(frame->wall_x2, 360));
		draw_text(home, "FULL_WALL_LEN", frame,
			vec2(frame->wall_x2 * 0.5, 160));
		draw_text(home, ft_ftoa(frame->full_wall_len, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 180));
		draw_text(home, "WALL_LEN", frame, vec2(frame->wall_x2 * 0.5, 200));
		draw_text(home, ft_ftoa(frame->screen_wall_len, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 220));
		draw_text(home, "FULL_WALL_DIST", frame,
			vec2(frame->wall_x2 * 0.5, 240));
		draw_text(home, ft_ftoa(frame->full_wall_dist, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 260));
		draw_text(home, "VISIBLE_WALL_DIST", frame, vec2(frame->wall_x2 * 0.5, 280));
		draw_text(home, ft_ftoa(frame->visible_wall_dist, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 300));
		draw_text(home, "RATIO", frame, vec2(frame->wall_x2 * 0.5, 320));
		draw_text(home, ft_ftoa(frame->ratio, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 340));
		draw_text(home, "WALL_FRACT_LEN", frame, vec2(frame->wall_x2 * 0.5, 360));
		draw_text(home, ft_ftoa(frame->wall_fract_len, 4, 1), frame,
			vec2(frame->wall_x2 * 0.5, 380));
	}
}

static t_xy		calc_vert_texture(t_xyz current, float height,
							t_frame *frame, t_texture *tex)
{
	float	tex_x;
	float	tex_y;
	float	z;

	// current = inv_z(current);
	// z = 1 / current.z;
	// tex_x = current.x * z;
	// tex_y = current.y * z;
	tex_y = current.y / height * tex->h;
	if (frame->left.wall->x0.x == frame->left.l_pt.x
		&& frame->left.wall->x0.y == frame->left.l_pt.y)
		tex_x = current.x / frame->full_wall_len * tex->w * frame->tex_mult;
	else if (frame->left.wall == frame->right.wall)
		tex_x =  (frame->wall_fract_len + current.x) / frame->full_wall_len * tex->w * frame->tex_mult;
	else
		tex_x = (frame->full_wall_len - frame->screen_wall_len + current.x) /
		 		frame->full_wall_len * tex->w * frame->tex_mult;
	return (vec2(tex_x, tex_y));
}

/*
**
** full_wall_len grows way too fast, when player is closer to the wall.
** Result is the same when using just view ratios, which does not make any sense.
** This is due perspective divide, we are using naive texture mapping or affine texture mapping currently to map the textures.
** We need to correct the textures using perspective divide 1 / z by every 16 px.
*/
static void		draw_vertical_line(t_xyz p0, t_xyz p1,
							t_texture *tex, t_frame *frame)
{
	float	min;
	float	max;
	float	height;
	t_xy	tex_pixel;

	if (p0.x != p1.x)
		return ;
	min = ft_fmin(p0.y, p1.y);
	max = ft_fmax(p0.y, p1.y);
	height = max - min;
	while (min < max)
	{
		tex_pixel = calc_vert_texture(vec3(p0.x, min, p0.z), height, frame, tex);
		if (p0.x >= 0 && p0.x < SCREEN_WIDTH &&
			p1.y >= 0 && p1.y < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, p0.x,
				min, get_texel(tex_pixel.x, tex_pixel.y, tex));
		min++;
	}
}

void			draw_segment(t_frame *frame, t_texture *tex,
							t_home *home, t_player *plr)
{
	t_xyz		current;
	if (frame->left.wall->c != 'b')
		return ;
		
	calc_distances(frame, tex, plr);
	current = (t_xyz){0.0f, 0.0f, frame->top_left.z};
	frame->step.x = 1.0f;
	frame->step.y = (frame->top_left.y - frame->top_right.y) / frame->screen_wall_len;
	frame->step.z = (frame->top_left.z - frame->top_right.z) / frame->screen_wall_len;
	while (current.x + frame->top_left.x < frame->top_right.x)
	{
		draw_vertical_line(
			vec3(current.x + frame->top_left.x, frame->top_left.y - current.y, current.z),
			vec3(current.x + frame->top_left.x, frame->bottom_left.y + current.y, current.z),
			tex,
			frame);
		current = vec3_add(current, frame->step);
	}
	debug_wall(home, frame);
}


static void		draw_horizontal_line(t_xy p0, t_xy p1,
							t_texture *tex, t_frame *frame)
{
	float	min;
	t_xyz	obj;
	t_xy	tex_pixel;

	if (p0.y != p1.y)
		return ;
	obj.y = p0.y;
	obj.x = 0.0f;
	min = ft_fmin(p0.y, p1.y);
	while (obj.x < frame->screen_wall_len)
	{
		tex_pixel = calc_vert_texture(vec3(obj.x, obj.y, obj.z), frame->screen_wall_len, frame, tex);
		if (obj.x + frame->wall_x1 >= 0 &&
			obj.x + frame->wall_x1 < SCREEN_WIDTH &&
			obj.y + frame->wall_h_l >= 0 && obj.y + frame->wall_h_l < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, obj.x + frame->wall_x1,
				obj.y + min, get_texel(tex_pixel.x, tex_pixel.y, tex));
		obj.x++;
	}
}
