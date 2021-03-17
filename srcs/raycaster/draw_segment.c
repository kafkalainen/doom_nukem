/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/17 12:15:51 by jnivala          ###   ########.fr       */
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
		// draw_text(home, "FULL_WALL_LEN", frame,
		// 	vec2(frame->wall_x2 * 0.5, 160));
		// draw_text(home, ft_ftoa(frame->full_wall_len, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 180));
		// draw_text(home, "WALL_LEN", frame, vec2(frame->wall_x2 * 0.5, 200));
		// draw_text(home, ft_ftoa(frame->screen_wall_len, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 220));
		// draw_text(home, "FULL_WALL_DIST", frame,
		// 	vec2(frame->wall_x2 * 0.5, 240));
		// draw_text(home, ft_ftoa(frame->full_wall_dist, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 260));
		// draw_text(home, "VISIBLE_WALL_DIST", frame, vec2(frame->wall_x2 * 0.5, 280));
		// draw_text(home, ft_ftoa(frame->visible_wall_dist, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 300));
		// draw_text(home, "RATIO", frame, vec2(frame->wall_x2 * 0.5, 320));
		// draw_text(home, ft_ftoa(frame->ratio, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 340));
		// draw_text(home, "UNVISIBLE LEFTSIDE", frame, vec2(frame->wall_x2 * 0.5, 360));
		// draw_text(home, ft_ftoa(frame->unvisible_l_side, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 380));
		// draw_text(home, "INVZ", frame, vec2(frame->wall_x2 * 0.5, 400));
		// draw_text(home, ft_ftoa(frame->top_left.z, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 420));
		// draw_text(home, "UNVISIBLE RIGHTSIDE", frame, vec2(frame->wall_x2 * 0.5, 440));
		// draw_text(home, ft_ftoa(frame->unvisible_r_side, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 460));
		// draw_text(home, "WALL_FRACT_LEN", frame, vec2(frame->wall_x2 * 0.5, 400));
		// draw_text(home, ft_ftoa(frame->wall_fract_len, 4, 1), frame,
		// 	vec2(frame->wall_x2 * 0.5, 420));
		draw_text(home, "TOP_LEFT_UV: X", frame,
			vec2(frame->top_left.x, 20));
		draw_text(home, ft_ftoa(frame->uv_top_left.x, 4, 1), frame,
			vec2(frame->top_left.x, 40));
		draw_text(home, "TOP_LEFT_UV: Y", frame,
			vec2(frame->top_left.x, 60));
		draw_text(home, ft_ftoa(frame->uv_top_left.y, 4, 1), frame,
			vec2(frame->top_left.x, 80));
		draw_text(home, "TOP_LEFT_UV: Z", frame,
			vec2(frame->top_left.x, 100));
		draw_text(home, ft_ftoa(frame->uv_top_left.z, 4, 1), frame,
			vec2(frame->top_left.x, 120));
		draw_text(home, "BOTTOM_LEFT_UV: X", frame,
			vec2(frame->top_left.x, 400));
		draw_text(home, ft_ftoa(frame->uv_bottom_left.x, 4, 1), frame,
			vec2(frame->top_left.x, 420));
		draw_text(home, "BOTTOM_LEFT_UV: Y", frame,
			vec2(frame->top_left.x, 440));
		draw_text(home, ft_ftoa(frame->uv_bottom_left.y, 4, 1), frame,
			vec2(frame->top_left.x, 460));
		draw_text(home, "TOP_RIGHT_UV: X", frame,
			vec2(frame->top_right.x, 20));
		draw_text(home, ft_ftoa(frame->uv_top_right.x, 4, 1), frame,
			vec2(frame->top_right.x, 40));
		draw_text(home, "TOP_RIGHT_UV: Y", frame,
			vec2(frame->top_right.x, 60));
		draw_text(home, ft_ftoa(frame->uv_top_right.y, 4, 1), frame,
			vec2(frame->top_right.x, 80));
		draw_text(home, "TOP_RIGHT_UV: Z", frame,
			vec2(frame->top_right.x, 100));
		draw_text(home, ft_ftoa(frame->uv_top_right.z, 4, 1), frame,
			vec2(frame->top_right.x, 120));
		draw_text(home, "BOTTOM_RIGHT_UV: X", frame,
			vec2(frame->top_right.x, 400));
		draw_text(home, ft_ftoa(frame->uv_bottom_right.x, 4, 1), frame,
			vec2(frame->top_right.x, 420));
		draw_text(home, "BOTTOM_RIGHT_UV: Y", frame,
			vec2(frame->top_right.x, 440));
		draw_text(home, ft_ftoa(frame->uv_bottom_right.y, 4, 1), frame,
			vec2(frame->top_right.x, 460));
	}
}

static t_xy		calc_vert_texture(t_xyz current, float height,
							t_frame *frame, t_texture *tex)
{
	t_xyz	ndc;

	// ndc.z = current.z;
	ndc.y = current.y / height;
	if (frame->left.wall->x0.x == frame->left.l_pt.x
		&& frame->left.wall->x0.y == frame->left.l_pt.y)
		ndc.x = (current.x / frame->screen_wall_len) * frame->ratio;
	else
		ndc.x = frame->unvisible_l_side + (current.x / frame->screen_wall_len * frame->ratio);
	// ndc = inv_z(ndc);
	// ndc.x = ndc.x / ndc.z;
	// ndc.y = ndc.y / ndc.z;
	return (vec2(ndc.x * tex->w * frame->tex_mult, ndc.y * tex->h));
}


/*
**
** full_wall_len grows way too fast, when player is closer to the wall.
** Result is the same when using just view ratios, which does not make any sense.
** This is due perspective divide, we are using naive texture mapping or affine texture mapping currently to map the textures.
** New structure ideas:
** Wall start point and endpoint, and a counter to count where we currently exist.
** UV coordinates should be calculated at draw vertical line and incremented there. That gives less computing, and only one divide.
** We need to correct the textures using perspective divide 1 / z by every 16 px.
*/
static void		draw_vertical_line(t_xyz p0, t_xyz p1,
							t_texture *tex, t_frame *frame)
{
	float	min;
	float	max;
	float	height;
	t_xyz	obj;
	t_xy	tex_pixel;
	t_xyz	corr_texel;
	t_xyz	texel;

	if (p0.x != p1.x)
		return ;
	obj.x = p0.x - frame->top_left.x;
	obj.y = 0.0f;
	obj.z = p0.z;
	texel.x = frame->uv_top_left.x;
	texel.y = frame->uv_top_left.y;
	texel.z = frame->uv_top_left.z;
	min = ft_fmin(p0.y, p1.y);
	max = ft_fmax(p0.y, p1.y);
	height = max - min;
	while (obj.y < height)
	{
		corr_texel = inv_z(texel);
		if (p0.x >= 0 &&
			p0.x < SCREEN_WIDTH &&
			obj.y + min >= 0 && obj.y + min < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, p0.x,
				obj.y + min, get_texel(corr_texel.x * tex->w, corr_texel.y * tex->h, tex));
		obj.y++;
		texel.y += frame->uv_step.y;
	}
}

void			draw_segment(t_frame *frame, t_texture *tex,
							t_home *home, t_player *plr)
{
	// if (frame->left.wall->c != 'b')
	// 	return ;
	size_t		obj_x;
	size_t		obj_y;
	size_t		obj_z;
	float		height;

	obj_x = 0;
	obj_y = 0;
	calc_distances(frame, tex, plr);
	calc_texels(frame, tex);
	frame->step.y = (frame->top_left.y - frame->top_right.y) / frame->screen_wall_len;
	frame->step.z = (frame->top_left.z - frame->top_right.z) / frame->screen_wall_len;
	while (obj_x + frame->top_left.x < frame->top_right.x)
	{
		draw_vertical_line(
			vec3(frame->top_left.x + obj_x, frame->top_left.y, 0.0f),
			vec3(frame->top_left.x + obj_x, frame->bottom_left.y, 0.0f),
			tex,
			frame);
		frame->top_left.y = frame->top_left.y - frame->step.y;
		frame->bottom_left.y = frame->bottom_left.y + frame->step.y;
		frame->top_left.z = frame->top_left.z - frame->step.z;
		obj_x++;
		frame->uv_top_left.x += frame->uv_step.x;
		frame->uv_top_left.z += frame->uv_step.z;
	}
	// debug_wall(home, frame);
}
