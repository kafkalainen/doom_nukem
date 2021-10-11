/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:25 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/11 08:28:48 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_FUNCTIONS_H
# define DRAWING_FUNCTIONS_H

enum			e_texture_idx
{
	zero,
	space,
	wall0,
	wall1,
	wall2,
	wall3,
	wall4,
	small_window,
	large_window,
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
	military_keycard_sprite,
	hull_small_window,
	hull_large_window,
	poster_whole
};

/*
** Drawing functions
*/

void			calc_colours(Uint32 *bg, Uint32 *fg, float *lightness);
t_bool			check_for_valid_draw_range(t_steps *step);
t_triangle		create_projection(t_triangle *src);
void			death_animation(t_home *home, t_player *plr, Uint32 t);
void			draw_box(t_box box, t_buffer *buffer, Uint32 color);
void			draw_bbox_sector(t_editor_sector *sector, t_buffer *buffer,
					t_action *action);
void			draw_buttons(t_editor *editor, t_texture **textures);
void			draw_button(t_editor *editor, t_button *button, int i);
void			draw_compass_direction(t_buffer *buffer, t_xy *dir);
void			draw_convert_to_portal_line(t_editor *editor);
void			draw_crosshair(t_buffer *buffer);
void			draw_cutscene(t_buffer *buffer, t_player *plr,
					t_sector *sector);
void			draw_editor_sectors_bboxes(t_editor *editor, t_action *action);
void			draw_editor_sectors(t_editor *editor);
void			draw_editor_sector(t_editor *editor,
					t_editor_sector *sector_list,
					t_editor_walls *left_point, Uint32 color);
void			draw_editor_entities(t_editor *editor, t_texture **textures);
void			draw_editor_entity_links(t_entity_list *entity,
					t_editor *editor);
void			draw_entity_textfields(t_entity_list *entity, t_buffer *buffer,
					t_texture **textures);
void			draw_entity_link_line(t_editor *editor);
void			draw_fps(t_buffer *buffer, int nb_fps);
void			draw_frame(t_home *home, t_frame *frame, t_player *plr);
void			draw_game(t_home *home, t_frame *frame, t_player *plr);
void			draw_image(t_xy offset, t_texel *tex, t_buffer *buffer,
					float scale);
void			draw_image_static(t_xy offset, t_texel *tex,
					t_buffer *buffer, float scale);
void			draw_input_string(unsigned char *string,
					t_buffer *buffer, int help_text);
void			draw_multisprite_image(t_xy offset, t_texel *tex,
					t_buffer *buffer, t_xy scale);
void			draw_grid(t_buffer *buffer, t_action *action);
void			draw_heads_up_display(t_home *home,
					t_frame *frame, t_player *plr);
void			draw_help_text(t_action *action, t_buffer *buffer);
void			draw_horizontal_line(t_buffer *buffer, float *depth_buffer,
					t_texel *tex, t_steps *step);
void			draw_hud_ammo_left(t_buffer *buffer, t_player *plr);
void			draw_info(t_buffer *buffer);
void			draw_int_string_input(t_buffer *buffer, t_action *action,
					unsigned char **int_string);
void			draw_inventory_images(t_home *home,
					t_player *plr, t_buffer *buffer);
void			draw_inventory_slots(t_player *plr, t_buffer *buffer);
void			draw_line(t_xy p0, t_xy p1, Uint32 colour, t_buffer *buffer);
void			draw_muzzleflash(t_home *home, t_buffer *buffer,
					t_player *plr, t_xy offset);
void			draw_object_data(t_buffer *buffer, t_player *plr);
void			draw_rect(t_xy xy, t_xy wh, t_buffer *buffer, int color);
void			draw_sector(t_frame *frame, t_home *home, t_player *plr,
					int sector_idx);
void			draw_sector_special_info(t_editor *editor);
void			draw_sector_textfields(t_editor_sector *sector,
					t_buffer *buffer, t_texture **textures);
void			draw_segment(t_buffer *buffer, float *depth_buffer,
					t_texel *tex, t_steps *step);
void			draw_square(t_buffer *buffer, t_xy offset, int c, int s);
void			draw_tex_pixel(t_texture *tex, t_xyz texel,
					t_xy pixel, t_frame *frame);
void			draw_tex_triangle(t_buffer *buffer, float *depth_buffer,
					t_triangle *triangle, t_texel *tex);
void			draw_ui(t_editor *editor, t_texture **textures);
void			draw_wall_textfields(t_editor_walls *wall,
					t_buffer *buffer, t_texture **textures);
void			draw_weapon(t_home *home, t_buffer *buffer,
					t_player *plr, t_xy offset);
void			draw_wireframe(t_frame *frame, Uint32 colour);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);
Uint32			get_texel(t_uv *coord, t_uv *limits, Uint32 *pixels);
int				get_color_from_action_data(int i, t_action *action,
					int end_sector);
void			*optimized_memcpy(void *pixels, void *src, size_t size);
void			put_pixel(t_buffer *buffer, t_pxl_coords xy, Uint32 color);
void			render_buffer(Uint32 *buffer, SDL_Surface *screen_surface);
void			reset_depth_buffer(float *depth_buffer);
void			show_editor_usage(t_buffer *buffer);
void			update_editor_load_menu(t_buffer *buffer, t_action *action,
					char **map_names);

#endif
