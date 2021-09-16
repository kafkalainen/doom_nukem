/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity_link_management.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:19:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 12:33:29 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	link_entity_sector(t_entity_list *clicked, t_entity_list *start,
				t_editor_sector *clicked_sector, t_editor_sector *start_sector)
{
	if (!clicked_sector || !start_sector)
		return (false);
	if (clicked->entity_type == lamp)
	{
		clicked_sector->light.is_linked = start->is_linked;
		clicked_sector->light.state = start->state;
	}
	if (start->entity_type == lamp)
	{
		start_sector->light.is_linked = start->is_linked;
		start_sector->light.state = clicked->state;
	}
	return (true);
}

t_bool	link_entities(t_entity_list **entities, t_editor_sector **sectors,
		t_xy click, int current_entity)
{
	t_entity_list	*starting_link;
	t_editor_sector	*starting_link_sector;
	t_entity_list	*clicked_entity;
	t_editor_sector	*clicked_entity_sector;
	int				click_entity_idx;

	starting_link = get_entity_with_idx(entities, current_entity);
	clicked_entity = get_clicked_entity(entities, click, &click_entity_idx);
	if (!starting_link || !clicked_entity
		|| !link_allowed(starting_link, clicked_entity, entities, sectors))
		return (false);
	starting_link->is_linked = clicked_entity->sector_idx + 2;
	clicked_entity->is_linked = starting_link->is_linked;
	clicked_entity->state = starting_link->state;
	clicked_entity_sector = get_editor_sector_with_idx(sectors,
			clicked_entity->sector_idx);
	starting_link_sector = get_editor_sector_with_idx(sectors,
			starting_link->sector_idx);
	return (link_entity_sector(clicked_entity, starting_link,
			clicked_entity_sector, starting_link_sector));
}

void	update_linked_light_states(t_entity_list **entities,
		t_editor_sector **sectors, t_entity_list *starting_link,
		int state)
{
	t_entity_list	*ending_link;
	t_editor_sector	*ending_link_sector;
	t_editor_sector	*starting_link_sector;

	if (!starting_link)
		return ;
	ending_link = get_linked_entity(entities,
			starting_link->is_linked, starting_link->entity_idx);
	if (!ending_link)
		return ;
	starting_link_sector = get_editor_sector_with_idx(sectors,
			starting_link->sector_idx);
	ending_link_sector = get_editor_sector_with_idx(sectors,
			ending_link->sector_idx);
	if (!starting_link_sector || !ending_link_sector)
		return ;
	starting_link->state = state;
	ending_link->state = state;
	if (ending_link->entity_type == lamp)
		ending_link_sector->light.state = state;
	else if (starting_link->entity_type == lamp)
		starting_link_sector->light.state = state;
}

void	unlink_linked_light_links(t_entity_list **entities,
		t_editor_sector **sectors, t_entity_list *starting_link)
{
	t_entity_list	*ending_link;
	t_editor_sector	*starting_link_sector;
	t_editor_sector	*ending_link_sector;

	if (!starting_link)
		return ;
	ending_link = get_linked_entity(entities,
			starting_link->is_linked, starting_link->entity_idx);
	if (!ending_link)
		return ;
	starting_link_sector = get_editor_sector_with_idx(sectors,
			starting_link->sector_idx);
	ending_link_sector = get_editor_sector_with_idx(sectors,
			ending_link->sector_idx);
	if (!starting_link_sector || !ending_link_sector)
		return ;
	starting_link->is_linked = 0;
	ending_link->is_linked = 0;
	if (ending_link->entity_type == lamp)
		ending_link_sector->light.is_linked = 0;
	else if (starting_link->entity_type == lamp)
		starting_link_sector->light.is_linked = 0;
}
