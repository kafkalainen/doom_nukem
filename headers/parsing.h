/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:10:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/06 10:09:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void			add_point(t_wall **walls, t_wall *wall);
int				add_points(t_sector *sector, unsigned char *buf,
					unsigned int **pos, ssize_t size);
void			add_surface(t_surface **point, t_surface *new);
void			add_to_middle(t_wall **current_wall, t_wall *new_wall);
Uint32			assign_entity_properties(t_home *home);
void			calc_map_properties(t_home *home, t_player *plr);
float			calc_distance_to_ceiling(t_sector *sector, t_xyz *new_loc);
void			calc_light_sources(t_home *home);
void			calc_unit_normals(t_home *home);
int				change_door_to_portal(int door);
int				check_if_lines_cut(t_sector *sector);
int				check_if_sector_has_same_points(t_sector *sector);
Uint32			check_if_same_point(t_xyz a, t_xyz b);
Uint32			check_portal_floor_difference(t_wall *portal,
					t_wall *portal_behind);
Uint32			check_portal_ceiling_difference(t_wall *portal,
					t_wall *portal_behind);
void			close_linkedlist(t_wall **point);
void			close_surface_list(t_surface **head);
void			free_entities(t_home *home);
int				free_points(t_wall **head, unsigned int nbr_of_walls);
t_sector		*free_sector(t_sector **sector);
void			free_sectors(t_home *home);
int				free_sectors_and_exit(int error_code, t_home *home);
void			free_sectors_n(t_home *home, size_t	n);
int				free_surfaces(t_surface **head, unsigned int nbr_of_surfaces);
void			initialize_top_texels(t_triangle *top);
void			initialize_bottom_texels(t_triangle *bottom);
void			initialize_sector_pointers(t_sector *new_sector);
void			initialize_door(t_wall *wall, t_point_data *left,
					t_point_data *right);
void			initialize_switches(t_wall *wall, t_point_data *left);
void			initialize_wall_triangles(t_wall *wall, t_point_data *left,
					t_point_data *right);
t_sector		*get_sector_data(unsigned char *buf, unsigned int *pos,
					ssize_t size);
int				map_texel(t_surface *surface, t_sector *sector);
t_surface		*new_surface(t_wall *data, t_xyz *start, int idx, char choice);
char			*parse_colour_data(char *ptr, t_texture *tex);
int				parse_coordinates(t_point_data *data, unsigned int ***pos,
					unsigned char **buf, ssize_t size);
int				parse_entity_data(unsigned char *buf, t_home *home, ssize_t size);
int				parse_vertex_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_light_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_map_name(t_home *home, ssize_t size,
					unsigned char *buf, unsigned int **pos);
int				parse_story_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_sector_data(unsigned char *buf, t_player *plr,
				t_home *home, ssize_t size);
int				parse_pixel_data(char *ptr, t_texture *tex);
void			retrieve_adjacent_triangles_ceiling(t_triangle *tri,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			retrieve_adjacent_triangles_ground(t_triangle *tri,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			retrieve_adjacent_top_triangles_walls(t_wall *wall,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			retrieve_adjacent_bottom_triangles_walls(t_wall *wall,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			retrieve_adjacent_wall_triangles(t_triangle *tri,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			ceiling_retrieve_adjacent_triangles_ceiling(t_surface *surf,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
void			ground_retrieve_adjacent_triangles_ground(t_surface *surf,
					t_sector *sector, t_raster_queue *queue,
					Uint32 current_point);
int				set_to_null(t_texture **tex, int error);
unsigned int	triangulate_floor(t_sector *sector, char choice);
unsigned int	triangulate_ceiling(t_sector *sector, char choice);
Uint32			get_next_int_value(int *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_uint_value(Uint32 *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_float_value(float *nb, unsigned char *buf,
					unsigned int **pos, ssize_t size);
Uint32			get_next_string(char **str, unsigned char *buf,
					unsigned int **pos, ssize_t size);

#endif
