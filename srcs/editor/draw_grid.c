/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:09:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/01 14:59:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_cells_on_axis(t_action *action, int *start, int *cells_on_axis,
			char axis)
{
	int	offset_cells;

	if (action->scalarf != 0.0f)
	{
		*cells_on_axis = 2.0f / action->scalarf;
		if (axis == 'x')
			offset_cells = action->offsetf.x / action->scalarf;
		else
			offset_cells = action->offsetf.y / action->scalarf;
	}
	else
	{
		*cells_on_axis = 2.0f;
		if (axis == 'x')
			offset_cells = action->offsetf.x;
		else
			offset_cells = action->offsetf.y;
	}
	if (offset_cells >= 0)
	{
		*start -= offset_cells;
	}
	else
		*cells_on_axis -= offset_cells;
}

static void	draw_grid_horizontal(t_buffer *buffer, t_action *action)
{
	int					cells_on_y_axis;
	int					current_cell;
	int					val;

	current_cell = 0;
	calc_cells_on_axis(action, &current_cell, &cells_on_y_axis, 'y');
	while (current_cell <= cells_on_y_axis)
	{
		val = 0.5f * buffer->height * (current_cell
				* action->scalarf + action->offsetf.y);
		if (val < buffer->height)
			draw_line(
				vec2(TOOLBAR_WIDTH, val),
				vec2(buffer->width, val),
				get_color(0x808080), buffer);
		current_cell++;
	}
}

static void	draw_grid_vertical(t_buffer *buffer, t_action *action)
{
	int					cells_on_x_axis;
	int					current_cell;
	int					val;

	current_cell = 0;
	calc_cells_on_axis(action, &current_cell, &cells_on_x_axis, 'x');
	while (current_cell <= cells_on_x_axis)
	{
		val = TOOLBAR_WIDTH + (0.5f * (buffer->width - TOOLBAR_WIDTH)
				* (current_cell * action->scalarf + action->offsetf.x));
		if (val < buffer->width && val >= TOOLBAR_WIDTH)
			draw_line(
				vec2(val, 0),
				vec2(val, buffer->height), get_color(0x808080), buffer);
		current_cell++;
	}
}

static void	draw_axes(t_buffer *buffer, t_action *action)
{
	t_xy				origo;
	t_plx_modifier		mod;
	t_box				box;

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
	box.start = origo;
	box.end = vec2(origo.x + 4.0f, origo.y + 4.0f);
	draw_box(box, buffer, get_color(yellow));
}

void	draw_grid(t_buffer *buffer, t_action *action)
{
	draw_grid_horizontal(buffer, action);
	draw_grid_vertical(buffer, action);
	draw_axes(buffer, action);
}
