/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:27:22 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/18 11:51:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void		draw_tex_pixel(SDL_Surface *tex, t_screen_xy pixel,
	t_screen_xy coord, SDL_Surface *draw_surf)
{
	Uint32		color;

	SDL_LockSurface(tex);
	color = get_pixel(tex, pixel.y, pixel.x);
	SDL_UnlockSurface(tex);
	put_pixel(draw_surf, coord.x, coord.y, color);
}
