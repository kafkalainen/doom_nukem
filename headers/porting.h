/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:55:49 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/02 13:51:17 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTING_H
# define PORTING_H

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

#endif
