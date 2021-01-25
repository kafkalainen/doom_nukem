/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:55:49 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/25 16:51:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTING_H
# define PORTING_H

/*
** PNG Encode/Decode functions
*/

void	init_textures(t_home *home);
void	load_texture(char *path, t_home *home, int i);
void	*convert_to_uint32(Uint32 *dest, SDL_Surface *image);
Uint32	swap_channels(Uint32 color);
Uint32	*load_texture_from_map_data(char *line);
/*
** Audio Encode/Decode funtions
*/

#endif
