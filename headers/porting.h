/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:55:49 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/22 14:01:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTING_H
# define PORTING_H

/*
** PNG Encode/Decode functions
*/

void	init_textures(t_home *home);
void	load_texture(char *path, t_home *home, int i);
void	*memory_copy(Uint32 *dest, SDL_Surface *image);
Uint32	swap_channels(Uint32 color);

/*
** Audio Encode/Decode funtions
*/

#endif
