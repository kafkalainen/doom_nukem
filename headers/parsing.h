/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:10:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/07 12:11:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void			add_point(t_wall **walls, t_wall *wall);
int				add_points(t_sector *sector, unsigned char *buf,
				unsigned int **pos);
void			calc_slanted_floors(t_home *home);
void			calc_wall_and_floor_properties(t_home *home);
int				check_if_lines_cut(t_sector *sector);
int				check_if_sector_has_same_points(t_sector *sector);
void			close_linkedlist(t_wall **point);
int				free_points(t_wall **head, unsigned int nbr_of_walls);
void			free_sectors(t_home *home);
int				set_to_null(t_texture **tex, int error);
int				free_sectors_and_exit(int error_code, t_home *home, size_t n);
void			free_sectors_n(t_home *home, size_t	n);
t_sector		*get_sector_data(unsigned char *buf, unsigned int *pos);
char			*parse_colour_data(char *ptr, t_texture *tex);
int				parse_coordinates(t_point_data *data, unsigned int ***pos,
					unsigned char **buf);
int				parse_number_data(t_sector *new_sector, unsigned char *buf,
					unsigned int *pos);
int				parse_sector_data(unsigned char *buf, t_home *home);
int				parse_pixel_data(char *ptr, t_texture *tex);
int				parse_xpm_data(unsigned char *buf, t_texture **tex);
t_surface		*new_surface(t_wall *data, t_xyz *start, int idx, char choice);
void			add_surface(t_surface **point, t_surface *new);
void			close_surface_list(t_surface **head);
int				free_surfaces(t_surface **head, unsigned int nbr_of_surfaces);
unsigned int	triangulate_floor_and_ceiling(t_sector *sector, char choice);

#endif
