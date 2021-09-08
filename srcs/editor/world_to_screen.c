/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:06:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 16:30:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	world_to_screen(t_xy world_coord, float scalarf, t_xy offsetf,
		t_buffer *buffer)
{
	t_xy		offset;
	t_xy		screen;

	offset.x = offsetf.x * (buffer->width - TOOLBAR_WIDTH) * 0.5f;
	offset.y = offsetf.y * buffer->height * 0.5f;
	screen = vec2_mul(vec2(world_coord.x, world_coord.y), scalarf);
	screen.x = TOOLBAR_WIDTH + 0.5f * (buffer->width - TOOLBAR_WIDTH)
			+ 0.5f * (buffer->width - TOOLBAR_WIDTH) * screen.x + offset.x;
	screen.y = buffer->height - (0.5 * buffer->height
			+ 0.5 * buffer->height * screen.y) + offset.y;
	return (screen);
}
