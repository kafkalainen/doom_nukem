/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/06 16:02:01 by jnivala          ###   ########.fr       */
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
	bullet,
	power_station_ready,
	power_station_depleted,
	button_on,
	button_off,
	lamp_on,
	lamp_off,
	bullet_decal,
	muzzleflash,
	ammo_pack_sprite,
	cleaning_keycard_sprite,
	engineering_keycard_sprite,
	military_keycard_sprite
};

/*
** Drawing functions
*/

float		calculate_lumel_offset(float from, float to, float t);
t_uvz		calculate_texel_offset(t_uvz from, t_uvz to, float t);
void		calculate_triangle(t_frame *frame, t_triangle *tri,
				t_texture *tex);
t_xy		center_to_screen(t_xy loc);
Uint32		colour_scale(Uint32 hex, float scale);
t_triangle	create_projection(t_triangle *src);
void		death_animation(t_home *home, t_player *plr, Uint32 t);
void		draw_crosshair(t_buffer *buffer);
void		draw_heads_up_display(t_home *home, t_frame *frame, t_player *plr);
void		draw_hud_ammo_left(t_buffer *buffer, t_player *plr);
void		draw_inventory_images(t_home *home, t_player *plr, t_buffer *buffer);
void		draw_inventory_slots(t_player *plr, t_buffer *buffer);
int			draw_line(t_xy p0, t_xy p1, Uint32 colour, t_buffer *buffer);
void		draw_muzzleflash(t_home *home, t_buffer *buffer,
				t_player *plr, t_xy offset);
void		draw_object_data(t_buffer *buffer, t_player *plr);
void		draw_rect_center(t_xy xy, t_xy wh, t_frame *frame);
void		draw_rect(t_xy xy, t_xy wh, t_buffer *buffer, int color);
void		draw_square(t_buffer *buffer, t_xy offset, int c, int s);
void		draw_tex_pixel(t_texture *tex, t_xyz texel,
				t_xy pixel, t_frame *frame);
int			draw_tex_triangle(t_buffer *buffer, float *depth_buffer,
				t_triangle *triangle, t_texel *tex);
int			draw_sector(t_frame *frame, t_home *home, t_player *plr,
				int sector_idx);
void		draw_weapon(t_home *home, t_buffer *buffer,
				t_player *plr, t_xy offset);
void		draw_frame(t_home *home, t_frame *frame, t_player *plr);
void		draw_info(t_frame *frame, t_player *plr, int nb_fps);
void		draw_segment(t_buffer *buffer, float *depth_buffer, t_texel *tex,
				t_steps *step);
int			draw_horizontal_line(t_buffer *buffer, float *depth_buffer,
				t_texel *tex, t_steps *step);
void		draw_wireframe(t_frame *frame, Uint32 colour);
Uint32		get_pixel(SDL_Surface *surface, int x, int y);
Uint32		get_texel(t_uv *coord, t_uv *limits, Uint32 *pixels);
void		*optimized_memcpy(void *pixels, void *src, size_t size);
void		put_pixel(t_buffer *buffer, t_pxl_coords xy, Uint32 color);
void		render_buffer(Uint32 *buffer, SDL_Surface *screen_surface);
void		reset_depth_buffer(float *depth_buffer);
t_triangle	rotate_triangle(t_triangle *src, float angle, char dir);
t_triangle	scale_triangle(t_triangle *src, t_xyz scale);
void		set_lighting(t_lighting *light, t_triangle *tri);
t_xyz		translate_point(t_xyz *src, t_xyz translation);
t_triangle	translate_triangle(t_triangle *src, t_xyz translation);

#endif
