/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:55:49 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 18:55:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTING_H
# define PORTING_H

# define READ_BREAKER '#'
# define BUF_SIZE 30000
# define XPM_BUF_SIZE 200000

int	create_map_file(t_home *home);
int	get_next_breaker(unsigned char *buf);
Uint32	get_floor(int floor_colour);
int	load_map_file(t_home *home, char *path);
int	validate_sectors_data(t_home *home);

/*
** PNG Encode/Decode functions
*/

void		init_textures(t_home *home);
void		load_texture(char *path, t_home *home, int i);
void		*convert_to_uint32(Uint32 *dest, t_texture *image);
void		clear_buffer(Uint32 *buffer);
Uint32		swap_channels(Uint32 color);
t_texture	*load_texture_from_map_data(char *line);
Uint32		get_texel(int x, int y, t_texture *tex);
void		put_texel(Uint32 *buffer, int x, int y, Uint32 color);
void		free_array(unsigned char **array);

/*
** Audio Encode/Decode funtions
*/

/*
** File creation, writing and reading functions
*/

# define WRITE_BREAKER "#"
# define READ_BREAKER '#'

int		create_map_file(t_home *home);
int		open_file(t_home *home, char *path);
int		open_map_file(t_home *home, char *path);

#endif
