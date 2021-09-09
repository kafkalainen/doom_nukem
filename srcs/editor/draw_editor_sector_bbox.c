/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_sector_bbox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:31:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 09:33:01 by jnivala          ###   ########.fr       */
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
	// point1 = sector->bbox.start.x * action->scalar + action->offset.x;
	// point2 = sector->bbox.start.y * action->scalar + action->offset.y;
	// point3 = sector->bbox.end.x * action->scalar + action->offset.x;
	// point4 = sector->bbox.end.y * action->scalar + action->offset.y;
	if (action->selected_sector == sector->idx_sector)
		color = get_color(lightgreen);
	else
		color = get_color(blue);
	draw_box(bbox_scaled, buffer, color);
	// draw_rect(bbox_scaled.start, vec2(ft_fabsf(bbox_scaled.start.x - bbox_scaled.end.x),
	// 	ft_fabsf(bbox_scaled.start.x)), buffer, color);
}
