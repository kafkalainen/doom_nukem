/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sector_bbox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:31:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 09:35:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_bbox_sector(t_sector_list *sector, t_buffer *buffer,
		t_action *action)
{
	Uint32	color;
	t_box	bbox_scaled;

	bbox_scaled.start = world_to_screen(sector->bbox.start, action->scalarf,
		action->offsetf, buffer);
	bbox_scaled.end = world_to_screen(sector->bbox.end, action->scalarf,
		action->offsetf, buffer);
	if (action->selected_sector == sector->idx_sector)
		color = get_color(lightgreen);
	else
		color = get_color(blue);
	draw_box(bbox_scaled, buffer, color);
}
