/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:36:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/24 17:19:58 by jnivala          ###   ########.fr       */
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

// static void	draw_minimapper(Uint32 *buffer)
// {
// 	t_xy	offset;
// 	t_xy	p0;
// 	t_xy	p1;
// 	t_xy	p2;
// 	t_xy	p3;
// 	float	mult;

// 	mult = 0.7f;
// 	offset = (t_xy){1.0f, 1.0f};
// 	p0 = (t_xy){0.0f, 0.0f};
// 	p1 = (t_xy){0.0f, 1.0f};
// 	p2 = (t_xy){1.0f, 1.0f};
// 	p3 = (t_xy){1.0f, 0.0f};
// 	p0 = vec2_add(p0, offset);
// 	p1 = vec2_add(p1, offset);
// 	p2 = vec2_add(p2, offset);
// 	p3 = vec2_add(p3, offset);
// 	p0 = vec2_mul(p0, mult);
// 	p1 = vec2_mul(p1, mult);
// 	p2 = vec2_mul(p2, mult);
// 	p3 = vec2_mul(p3, mult);
// 	p0 = vec2(p0.x * SCREEN_WIDTH * 0.5f, p0.y * SCREEN_HEIGHT * 0.5f);
// 	p1 = vec2(p1.x * SCREEN_WIDTH * 0.5f, p1.y * SCREEN_HEIGHT * 0.5f);
// 	p2 = vec2(p2.x * SCREEN_WIDTH * 0.5f, p2.y * SCREEN_HEIGHT * 0.5f);
// 	p3 = vec2(p3.x * SCREEN_WIDTH * 0.5f, p3.y * SCREEN_HEIGHT * 0.5f);
// 	draw_line(p0, p1, get_color(red), buffer);
// 	draw_line(p1, p2, get_color(green), buffer);
// 	draw_line(p2, p3, get_color(blue), buffer);
// 	draw_line(p3, p0, get_color(white), buffer);
// }

void	update_screen(t_home *home, t_frame *frame, t_player *plr)
{
	frame->last_frame = SDL_GetTicks();
	// draw_minimapper(frame->buffer);
	draw_frame(home, frame, plr);
}
