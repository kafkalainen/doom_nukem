/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:34:26 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/22 17:22:50 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy			scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

Uint32			get_pixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint32	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint32 *)((Uint8 *)surface->pixels +
		y * surface->pitch + x * bpp);
	return (*p);
}

void			put_pixel(Uint32 *buffer, int x, int y, int color)
{
	Uint32		*pixel;

	if (x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1 || x < 0 || y < 0)
		return ;
	// buffer[(SCREEN_WIDTH * y) + x] = color;
	pixel = buffer + (SCREEN_WIDTH * y) + x;
	*pixel = color;
}
