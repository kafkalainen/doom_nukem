/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:10:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 08:39:18 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void			add_point(t_wall **walls, t_wall *wall);
int				add_points(t_sector *sector, unsigned char *buf,
					unsigned int **pos, ssize_t size);
void			add_surface(t_surface **point, t_surface *new);
void			add_to_middle(t_wall **current_wall, t_wall *new_wall);
Uint32			assign_entity_properties(t_home *home, t_xyz plr_pos);
int				set_entity_health(t_uint type, float difficulty);
void			assign_projectiles(t_home *home);
void			calc_lift_doors(t_home *home);
void			calc_map_properties(t_home *home, t_player *plr);
t_bool			calc_distance_to_ceiling(t_sector *sector, t_xyz *new_loc,
					float *dist);
t_bool			calc_distance_to_ground(t_sector *sector, t_xyz *new_loc,
					float *dist);
void			calc_light_sources(t_home *home);
void			calc_wall_asset_locations(t_home *home);
void			calc_entity_locations(t_home *home);
void			calc_plr_position(t_sector *sector, t_player *plr);
void			calc_unit_normals(t_home *home);
int				change_door_to_portal(int door);
void			check_portal_floor_difference(t_wall *portal,
					t_wall *portal_behind, t_bool *validation);
void			check_portal_ceiling_difference(t_wall *portal,
					t_wall *portal_behind, t_bool *validation);
int				close_linkedlist(t_wall **point);
void			close_surface_list(t_surface **head);
void			free_entities(t_home *home);
void			free_projectiles(t_home *home);
t_bool			free_points(t_wall **head, unsigned int nbr_of_walls);
t_sector		*free_sector(t_sector **sector);
void			free_sectors(t_home *home);
int				free_sectors_and_exit(int error_code, t_home *home);
void			free_sectors_n(t_home *home, size_t	n);
void			free_surfaces(t_surface **head, unsigned int nbr_of_surfaces);
void			generate_door(t_wall *portal, t_uint *nb_of_walls);
void			generate_window(t_wall *portal, t_uint *nb_of_walls);
Uint32			get_next_int_value(int *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_uint_value(Uint32 *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_float_value(float *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_string(char **str, unsigned char *buf,
					unsigned int **pos, ssize_t size);
t_sector		*get_sector_data(unsigned char *buf, unsigned int *pos,
					ssize_t size);
int				get_door_lock(int door_idx);
void			initialize_bot_triangle(int type, t_triangle *bot, t_xy size);
void			initialize_bottom_texels(t_triangle *bottom);
void			initialize_top_texels(t_triangle *top);
void			initialize_top_triangle(int type, t_triangle *top, t_xy size);
void			initialize_sector_pointers(t_sector *new_sector);
void			initialize_door(t_wall *wall, t_point_data *left,
					t_point_data *right);
void			initialize_lamp_to_ceiling(t_entity *entity, t_home *home);
void			initialize_switches(t_wall *wall, t_point_data *left);
void			initialize_wall_triangles(t_wall *wall, t_point_data *left,
					t_point_data *right);
int				map_texel(t_surface *surface, t_sector *sector);
t_surface		*new_surface(t_wall *data, t_xyz *start, int idx, char choice);
char			*parse_colour_data(char *ptr, t_texture *tex);
int				parse_coordinates(t_point_data *data, unsigned int ***pos,
					unsigned char **buf, ssize_t size);
int				parse_entity_data(unsigned char *buf, t_home *home,
					ssize_t size);
int				parse_sector_header_data(t_sector *new_sector,
					unsigned char *buf, unsigned int *pos, ssize_t size);
int				parse_light_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_map_name(char **chosen_map, ssize_t size,
					unsigned char *buf, unsigned int **pos);
int				parse_story_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_sector_data(unsigned char *buf, t_player *plr,
					t_home *home, ssize_t size);
int				parse_pixel_data(char *ptr, t_texture *tex);
void			resize_portal(t_wall *front, t_wall *behind, char c);
int				set_to_null(t_texture **tex, int error);
unsigned int	triangulate_floor(t_sector *sector, char choice);
unsigned int	triangulate_ceiling(t_sector *sector, char choice);
t_bool			vec3_check_if_same_point(t_xyz a, t_xyz b);
t_bool			vec2_check_if_same_point(t_xy a, t_xy b);

#endif
