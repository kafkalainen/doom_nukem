/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:10:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/01 14:41:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void			add_point(t_wall **walls, t_wall *wall);
int				add_points(t_sector *sector, unsigned char *buf,
					unsigned int **pos, ssize_t size);
void			add_surface(t_surface **point, t_surface *new);
void			add_to_middle(t_wall **current_wall, t_wall *new_wall);
void			calc_slanted_floors(t_home *home);
void			calc_map_properties(t_home *home, t_player *plr);
void			calc_top_normal_averages(t_sector *sector,
					t_raster_queue *queue);
void			calc_bottom_normal_averages(t_sector *sector,
					t_raster_queue *queue);
void			calc_ceiling_normal_averages(t_sector *sector,
					t_raster_queue *queue);
float			calc_distance_to_ceiling(t_sector *sector, t_xyz *new_loc);
void			calc_ground_normal_averages(t_sector *sector,
					t_raster_queue *queue);
void			calc_light_sources(t_home *home);
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
int				free_points(t_wall **head, unsigned int nbr_of_walls);
void			free_sectors(t_home *home);
int				free_sectors_and_exit(int error_code, t_home *home);
void			free_sectors_n(t_home *home, size_t	n);
int				free_surfaces(t_surface **head, unsigned int nbr_of_surfaces);
void			initialize_triangles(t_wall *wall, t_point_data *left,
					t_point_data *right);
void			initialize_top_texels(t_wall *wall);
void			initialize_bottom_texels(t_wall *wall);
t_sector		*get_sector_data(unsigned char *buf, unsigned int *pos,
					ssize_t size);
int				map_texel(t_surface *surface, t_sector *sector);
t_surface		*new_surface(t_wall *data, t_xyz *start, int idx, char choice);
char			*parse_colour_data(char *ptr, t_texture *tex);
int				parse_coordinates(t_point_data *data, unsigned int ***pos,
					unsigned char **buf, ssize_t size);
int				parse_vertex_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos, ssize_t size);
int				parse_light_data(t_sector *new_sector, unsigned char *buf,
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

#endif
