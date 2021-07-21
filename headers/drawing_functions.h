/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/21 21:23:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_FUNCTIONS_H
# define DRAWING_FUNCTIONS_H

enum e_texture_idx
{
	zero,
	space,
	wall0,
	wall1,
	wall2,
	wall3,
	wall4,
	wall5,
	wall6,
	wall7,
	wall8,
	wall9,
	surf0,
	surf1,
	surf2,
	surf3,
	surf4,
	surf5,
	surf6,
	surf7,
	surf8,
	surf9,
	door,
	hud,
	weapon0,
	weapon1,
	enemy0,
	enemy1,
	enemy2,
	enemy3,
	projectile,
	power_station_ready,
	power_station_depleted,
	button_on,
	button_off,
	lamp_on,
	lamp_off,
};

/*
** Drawing functions
*/

void		calc_average_unit_normals(t_home *home);
float		calculate_lumel_offset(float from, float to, float t);
t_uvz		calculate_texel_offset(t_uvz from, t_uvz to, float t);
t_xy		center_to_screen(t_xy loc);
Uint32		colour_scale(Uint32 hex, float scale);
t_triangle	create_projection(t_triangle *src);
int			draw_line(t_xy start, t_xy end, Uint32 color, Uint32 *buffer);
void		draw_rect_center(t_xy xy, t_xy wh, t_frame *frame);
void		draw_rect(t_xy xy, t_xy wh, Uint32 *buffer, int color);
void		draw_square(Uint32 *buffer, t_xy offset, int c, int s);
void		draw_tex_pixel(t_texture *tex, t_xyz texel,
			t_xy pixel, t_frame *frame);
int			draw_sector(t_frame *frame, t_home *home, t_player *plr,
			int sector_idx);
int			draw_cube(t_frame *frame, t_home *home, t_player *plr);
void		draw_wireframe(t_frame *frame, Uint32 colour);
Uint32		get_pixel(SDL_Surface *surface, int x, int y);
Uint32		get_texel(t_uv *coord, t_uv *limits, Uint32 *pixels);
void		put_pixel(Uint32 *buffer, int x, int y, Uint32 color);
t_triangle	scale_triangle(t_triangle *src, t_xyz scale);
void		*optimized_memcpy(void *pixels, void *src, size_t size);
void		render_buffer(Uint32 *buffer, SDL_Surface *screen_surface);
void		set_lighting(t_lighting *light, t_triangle *tri);
t_xyz		translate_point(t_xyz *src, t_xyz translation);
t_triangle	translate_triangle(t_triangle *src, t_xyz translation);
t_triangle	rotate_triangle(t_triangle *src, float angle, char dir);
void		calculate_triangle(t_frame *frame, t_triangle *tri,
			t_texture *tex);
int			draw_tex_triangle(Uint32 *buffer, float *depth_buffer,
			t_triangle *triangle, t_texel *tex);
void		reset_depth_buffer(float *depth_buffer);

#endif
