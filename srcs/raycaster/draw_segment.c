/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:50:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/09 14:20:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


static void		debug_wall(t_home *home, t_frame *frame)
{	
	if (frame->left.wall->c == 'b')
	{
		draw_text(home, "LEFT", frame, vec2(frame->wall_x1, 220));
		draw_text(home, ft_ftoa(frame->wall_x1, 2, 1), frame, vec2(frame->wall_x1, 240));
		draw_text(home, "LEFT_PT: X and Y", frame, vec2(20, 260));
		draw_text(home, ft_ftoa(frame->left.l_pt.x, 2, 1), frame, vec2(frame->wall_x1, 280));
		draw_text(home, ft_ftoa(frame->left.l_pt.y, 2, 1), frame, vec2(frame->wall_x1, 300));
		draw_text(home, "FULL_LEN_LEFT_PT: X and Y", frame, vec2(20, 320));
		draw_text(home, ft_ftoa(frame->left.wall->x0.x, 2, 1), frame, vec2(frame->wall_x1, 340));
		draw_text(home, ft_ftoa(frame->left.wall->x0.y, 2, 1), frame, vec2(frame->wall_x1, 360));
		draw_text(home, "RIGHT", frame, vec2(frame->wall_x2 * 0.75, 220));
		draw_text(home, ft_ftoa(frame->wall_x2, 2, 1), frame, vec2(frame->wall_x2, 240));
		draw_text(home, "RIGHT_PT: X and Y", frame, vec2(frame->wall_x2 * 0.75, 260));
		draw_text(home, ft_ftoa(frame->left.r_pt.x, 2, 1), frame, vec2(frame->wall_x2, 280));
		draw_text(home, ft_ftoa(frame->left.r_pt.y, 2, 1), frame, vec2(frame->wall_x2, 300));
		draw_text(home, "FULL_LEN_RIGHT_PT: X and Y", frame, vec2(frame->wall_x2, 320));
		draw_text(home, ft_ftoa(frame->left.wall->next->x0.x, 2, 1), frame, vec2(frame->wall_x2, 340));
		draw_text(home, ft_ftoa(frame->left.wall->next->x0.y, 2, 1), frame, vec2(frame->wall_x2, 360));
		draw_text(home, "FULL_WALL_LEN", frame, vec2(frame->wall_x2 * 0.5, 160));
		draw_text(home, ft_ftoa(frame->full_wall_len, 4, 1), frame, vec2(frame->wall_x2 * 0.5, 180));
		draw_text(home, "WALL_LEN", frame, vec2(frame->wall_x2 * 0.5, 200));
		draw_text(home, ft_ftoa(frame->wall_len, 4, 1), frame, vec2(frame->wall_x2 * 0.5, 220));	
	}
}

// static void		draw_horizontal_line(t_xy p0, t_xy p1,
// 							t_texture *tex, SDL_Surface *surf)
// {
// 	float	min;
// 	float	max;

// 	if (p0.y != p1.y)
// 		return ;
// 	min = ft_fmin(p0.x, p1.x);
// 	max = ft_fmax(p0.x, p1.x);
// 	while (min < max)
// 	{
// 		if (min >= 0 && min < SCREEN_WIDTH && 
// 			p0.y >= 0 && p0.y < SCREEN_HEIGHT)
// 			put_pixel(surf, min, p1.y, get_texel(min, p1.y, tex));
// 		min++;
// 	}
// }


// static t_xy		calc_hor_texture(t_xy current, float height, t_frame *frame)
// {
// 	float	perp_dist_step;
// 	float	current_perp_dist;

// 	perp_dist_step = (frame->l_perp_dist - frame->r_perp_dist) / frame->wall_len;
// 	current_perp_dist = perp_dist_step != 0 ? current.x * perp_dist_step : frame->l_perp_dist;
// 	return (vec2(current_perp_dist, 0));
// }


static t_xy		calc_vert_texture(t_xy current, float height, t_frame *frame, t_texture *tex)
{
	float	tex_x;
	float	tex_y;
	t_xy	tex_pixel;

	tex_y = current.y / height * tex->h;
	if (frame->left.wall->x0.x == frame->left.l_pt.x
		&& frame->left.wall->x0.y == frame->left.l_pt.y)
		tex_x = current.x / frame->full_wall_len * tex->w * frame->tex_mult;
	else if (frame->left.wall == frame->right.wall)
		tex_x = (frame->wall_fract_len + current.x) / frame->full_wall_len * tex->w * frame->tex_mult;
	else 
		tex_x = (frame->full_wall_len - frame->wall_len + current.x) / frame->full_wall_len * tex->w * frame->tex_mult;
	tex_pixel = vec2(tex_x, tex_y);
	return (tex_pixel);
}

static void		draw_vertical_line(t_xy p0, t_xy p1,
							t_texture *tex, t_frame *frame)
{
	float	min;
	float	max;
	float	height;
	t_xy	obj;
	t_xy	tex_pixel;

	if (p0.x != p1.x)
		return ;
	obj.x = p0.x;
	obj.y = 0.0f;
	min = ft_fmin(p0.y, p1.y);
	max = ft_fmax(p0.y, p1.y);
	height = max - min;
	while (obj.y < height)
	{
		tex_pixel = calc_vert_texture(vec2(obj.x, obj.y), height, frame, tex);
		if (obj.x + frame->wall_x1 >= 0 && obj.x + frame->wall_x1 < SCREEN_WIDTH && 
			obj.y + min >= 0 && obj.y + min < SCREEN_HEIGHT)
			put_pixel(frame->draw_surf, obj.x + frame->wall_x1, obj.y + min, get_texel(tex_pixel.x, tex_pixel.y, tex));
		obj.y++;
	}
}

void			draw_segment(t_frame *frame, t_texture *tex, 
							t_home *home, t_player *plr)
{
	float		step;
	float		z_step;
	float		obj_x;

	obj_x = 0.0f;
	calc_distances(frame, tex);
	z_step = get_distance(plr->pos, frame->left.l_pt) / 
				get_distance(plr->pos, frame->left.l_pt);
	step = (frame->wall_h_l - frame->wall_h_r) / frame->wall_len;
	while (obj_x + frame->wall_x1 < frame->wall_x2)
	{
		// draw_tex_line(
		// 	vec2(frame->wall_x1, 0),
		// 	vec2(frame->wall_x1, plr->pitch - frame->wall_h_l),
		// 	get_tex(-3, home->editor_tex),
		// 	frame->draw_surf
		// ); /*drawing ceiling*/
		// draw_tex_line(
		// 	vec2(frame->wall_x1, plr->pitch + frame->wall_h_l),
		// 	vec2(frame->wall_x1, 0),
		// 	get_tex(-3, home->editor_tex),
		// 	frame->draw_surf
		// ); /*drawing a floor*/
		draw_vertical_line(
			vec2(obj_x, plr->pitch - frame->wall_h_l),
			vec2(obj_x, plr->pitch + frame->wall_h_l),
			tex,
			frame); /*drawing a wall*/
		frame->wall_h_l = frame->wall_h_l - step;
		z_step -= frame->wall_len * z_step;
		obj_x++;
	}
}
