/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:36:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/20 11:48:25 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	render_buffer(Uint32 *buffer, SDL_Surface *screen_surface)
{
	SDL_LockSurface(screen_surface);
	optimized_memcpy(screen_surface->pixels,
		buffer, screen_surface->pitch * screen_surface->h);
	SDL_UnlockSurface(screen_surface);
}

void	update_screen(t_home *home, t_frame *frame, t_player *plr)
{
	draw_frame(home, frame, plr);
}
