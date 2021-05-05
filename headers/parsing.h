/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:10:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/05 12:02:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void		add_point(t_point **point, t_point *new);
int			add_points(t_sector *sector, unsigned char *buf,
				unsigned int **pos);
void		calc_normal_vectors(t_home *home);
int			check_if_lines_cut(t_sector *sector);
void		close_linkedlist(t_point **point);
int			free_points(t_point **head, unsigned int nbr_of_walls);
void		free_sectors(t_home *home);
int			set_to_null(t_texture **tex, int error);
int			free_sectors_and_exit(int error_code, t_home *home, size_t n);
void		free_sectors_n(t_home *home, size_t	n);
t_sector	*get_sector_data(unsigned char *buf, unsigned int *pos);
char		*parse_colour_data(char *ptr, t_texture *tex);
int			parse_coordinates(t_point_data *data, unsigned int ***pos,
				unsigned char **buf);
int			parse_number_data(t_sector *new_sector, unsigned char *buf,
				unsigned int *pos);
int			parse_sector_data(unsigned char *buf, t_home *home);
int			parse_pixel_data(char *ptr, t_texture *tex);
int			parse_xpm_data(unsigned char *buf, t_texture **tex);

#endif
