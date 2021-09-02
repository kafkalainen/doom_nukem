/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:34:26 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/02 17:00:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	scale(t_xy a)
{
	return (vec2(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE));
}

Uint32	get_pixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint32	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint32 *)((Uint8 *)surface->pixels
			+ y * surface->pitch + x * bpp);
	return (*p);
}

void	put_pixel(Uint32 *buffer, int x, int y, Uint32 color)
{
	Uint8	alpha;

	alpha = (color & 0xFF000000) >> 24;
	if (x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1
		|| x < 0 || y < 0 || alpha < 50)
		return ;
	*(buffer + (SCREEN_WIDTH * y) + x) = color;
}
