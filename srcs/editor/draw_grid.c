/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:09:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 11:36:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	draw_grid_horizontal(t_buffer *buffer, t_action *action)
{
	unsigned int	cells_on_y_axis;
	unsigned int	i;
	int				val;

	i = 0;
	cells_on_y_axis = 2.0f / action->scalarf;
	while (i <= cells_on_y_axis)
	{
		val = buffer->height * 0.5f * (i * action->scalarf
				+ (action->offsetf.y));
		if (val < buffer->height)
			draw_line(
				vec2(TOOLBAR_WIDTH, val),
				vec2(buffer->width, val),
				get_color(0x808080), buffer);
		i++;
	}
}

static void	draw_grid_vertical(t_buffer *buffer, t_action *action)
{
	unsigned int	cells_on_x_axis;
	unsigned int	i;
	int				val;

	i = 0;
	cells_on_x_axis = 2.0f / action->scalarf;
	while (i <= cells_on_x_axis)
	{
		val = TOOLBAR_WIDTH + (0.5f * (buffer->width - TOOLBAR_WIDTH)
				* (i * action->scalarf + (action->offsetf.x)));
		if (val < buffer->width && val >= TOOLBAR_WIDTH)
			draw_line(
				vec2(val, 0),
				vec2(val, buffer->height), get_color(0x808080), buffer);
		i++;
	}
}

static void	draw_axes(t_buffer *buffer, t_action *action)
{
	t_xy			origo;
	t_plx_modifier	mod;

	mod.size = 3;
	mod.len = 1;
	mod.colour = get_color(white);
	origo = vec2(
			TOOLBAR_WIDTH
			+ ((buffer->width - TOOLBAR_WIDTH) * 0.5f
				+ (action->offsetf.x * (buffer->width - TOOLBAR_WIDTH) * 0.5f))
			- 2.0f,
			buffer->height * 0.5f + (action->offsetf.y
				* buffer->height * 0.5f) - 2.0f);
	draw_line(origo, vec2(origo.x, origo.y - 40), mod.colour, buffer);
	draw_line(origo, vec2(origo.x + 40, origo.y), mod.colour, buffer);
	ft_str_pxl(buffer, vec2(origo.x + 30.0f, origo.y - 10.0f), "x", mod);
	ft_str_pxl(buffer, vec2(origo.x - 5.0f, origo.y - 40.0f), "y", mod);
	draw_rect(origo, vec2(4.0f, 4.0f), buffer, get_color(yellow));
}

void	draw_grid(t_buffer *buffer, t_action *action)
{
	draw_grid_horizontal(buffer, action);
	draw_grid_vertical(buffer, action);
	draw_axes(buffer, action);
}
