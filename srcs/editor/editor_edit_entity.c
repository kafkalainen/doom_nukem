/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_entity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:18:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	toggle_sector_light_state(t_editor *editor, t_entity_list *lamp,
			t_bool state)
{
	t_editor_sector	*sector;

	sector = NULL;
	if (is_linkable_entity(lamp->type) && lamp->is_linked < 2)
	{
		sector = get_editor_sector_with_idx(&editor->sector_list,
				lamp->sector_idx);
		if (sector)
			sector->light.state = state;
	}
}

static void	toggle_links(t_action *action, t_entity_list *entity,
			t_editor *editor)
{
	t_editor_sector	*sector;

	sector = NULL;
	if (is_linkable_entity(entity->type) && entity->is_linked == 1)
	{
		sector = get_editor_sector_with_idx(&editor->sector_list,
				entity->sector_idx);
		if (sector)
			sector->light.is_linked = 0;
		entity->is_linked = 0;
	}
	else if (is_linkable_entity(entity->type) && entity->is_linked == 0)
	{
		sector = get_editor_sector_with_idx(&editor->sector_list,
				entity->sector_idx);
		if (sector)
			sector->light.is_linked = 1;
		entity->is_linked = 1;
	}
	else if (is_linkable_entity(entity->type) && entity->is_linked > 1)
		unlink_linked_light_links(&editor->entity_list, &editor->sector_list,
			entity);
	action->toggle_entity_is_linked = 0;
}

static void	toggle_states(t_action *action, t_entity_list *entity,
			t_editor *editor)
{
	if (entity->state == false)
	{
		toggle_sector_light_state(editor, entity, true);
		entity->state = true;
	}
	else
	{
		toggle_sector_light_state(editor, entity, false);
		entity->state = false;
	}
	if (is_linkable_entity(entity->type) && entity->is_linked > 1)
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
		if (entity->is_revealed == false)
			entity->is_revealed = true;
		else
			entity->is_revealed = false;
		action->toggle_is_revealed = false;
	}
	else if (action->toggle_state)
		toggle_states(action, entity, editor);
	action->edit_entity = 0;
}
