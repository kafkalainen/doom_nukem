/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_entity_links.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:01:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_editor_entity_links(t_entity_list *entity, t_editor *editor)
{
	t_entity_list	*linked_entity;

	if (entity->is_linked > 1 && is_linkable_entity(entity->type))
	{
		linked_entity = get_linked_entity(&editor->entity_list,
				entity->is_linked, entity->entity_idx);
		if (linked_entity && is_linkable_entity(linked_entity->type))
		{
			draw_line(
				world_to_screen(vec2(linked_entity->pos.x,
						linked_entity->pos.z),
					editor->action.scalarf, editor->action.offsetf,
					&editor->buffer),
				world_to_screen(vec2(entity->pos.x, entity->pos.z),
					editor->action.scalarf, editor->action.offsetf,
					&editor->buffer),
				get_color(blue), &editor->buffer);
		}
	}
}
