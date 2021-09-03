/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:55:49 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/03 15:59:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTING_H
# define PORTING_H

# define READ_BREAKER '#'
# define BUF_SIZE 30000
# define XPM_BUF_SIZE 200000

int				get_next_breaker(unsigned char *buf);
int				load_map_file(t_player *plr, t_home *home);
int				validate_sectors_data(t_home *home, t_player *plr);
void			free_all_textures(t_texture **textures, int *nbr_of_textures);

/*
** PNG Encode/Decode functions
*/

void			init_textures(t_home *home);
void			load_texture(char *path, t_texture **tex_array, int i);
void			*convert_to_uint32(Uint32 *dest, t_texture *image);
void			clear_buffer(Uint32 *buffer);
Uint32			swap_channels(Uint32 color, int format);
t_texture		*load_texture_from_map_data(char *line);
void			free_array(unsigned char **array);
void			parse_texture_data(unsigned char *buf, t_home *home,
					unsigned int *pos, ssize_t size);
void			write_single_texture(t_texture *tex, int *fd,
					unsigned char *buf);
t_texture		*return_new_texture(t_png *png, int idx);
unsigned char	*create_write_buffer(t_texture *tex);
void			cycle_textures(t_home *home,
					struct dirent *dir_entry, DIR *dir);

/*
** Audio Encode/Decode funtions
*/

void			parse_audio_data(unsigned char *buf,
					unsigned int *pos, char *path, ssize_t size);
void			get_audio_data(t_audio_asset *asset, char *path);
int				create_temp_audio_file(unsigned char *buf,
					ssize_t size, char *path);

/*
** File creation, writing and reading functions
*/

# define WRITE_BREAKER "#"
# define READ_BREAKER '#'

int				create_map_file(t_home *home);
void			write_texture_data(int *fd, t_home *home);
void			write_audio_data(int *fd, char *path, char *asset_name);
int				open_file(t_home *home, char *path);
int				open_map_file(t_home *home, char *path);

#endif
