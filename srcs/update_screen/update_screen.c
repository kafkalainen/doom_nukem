/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:36:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/26 15:00:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**		Line 31 nulling:
**		might be inefficient
*/
void	*optimized_memcpy(void *pixels, void *src, size_t size)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	s = (char *)src;
	d = (char *)pixels;
	while (i < size)
	{
		d[i] = s[i];
		s[i] = 0;
		i++;
	}
	return (d);
}

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
