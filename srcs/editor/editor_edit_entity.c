/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_entity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:18:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 11:18:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	toggle_links(t_action *action, t_entity_list *entity, t_editor *editor)
{
	if (is_linkable_entity(entity->entity_type) && entity->is_linked == 1)
		entity->is_linked = 0;
	else if (is_linkable_entity(entity->entity_type) && entity->is_linked == 0)
		entity->is_linked = 1;
	else if (is_linkable_entity(entity->entity_type) && entity->is_linked > 1)
		unlink_linked_light_links(&editor->entity_list, &editor->sector_list,
			entity);
	action->toggle_entity_is_linked = 0;
}

static void toggle_states(t_action *action, t_entity_list *entity, t_editor *editor)
{
	if (entity->state == 0)
		entity->state = 1;
	else
		entity->state = 0;
	if (is_linkable_entity(entity->entity_type) && entity->is_linked > 1)
		update_linked_light_states(&editor->entity_list, &editor->sector_list,
			entity, entity->state);
	action->toggle_state = 0;
}

void	edit_entity(t_action *action, t_entity_list *entity, t_editor *editor)
{
	if (action->change_entity_type)
		rotate_through_entities(entity, action);
	else if (action->toggle_entity_is_linked)
		toggle_links(action, entity, editor);
	else if (action->toggle_is_revealed)
	{
		if (entity->is_revealed == 0)
			entity->is_revealed = 1;
		else
			entity->is_revealed = 0;
		action->toggle_is_revealed = 0;
	}
	else if (action->toggle_state)
		toggle_states(action, entity, editor);
	action->edit_entity = 0;
}
