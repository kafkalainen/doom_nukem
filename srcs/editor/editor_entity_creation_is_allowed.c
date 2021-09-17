/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity_creation_is_allowed.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:43:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 14:58:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	calc_entities_in_sector_with_type(t_entity_list **head,
		int sector_idx, int	entity_type)
{
	t_entity_list	*temp;
	int				count;

	count = 0;
	temp = *head;
	while (temp != NULL)
	{
		if (temp->entity_type == entity_type
			&& temp->sector_idx == sector_idx)
			count++;
		temp = temp->next;
	}
	return (count);
}

// if (action->create_powerstation) // cannot create on top of something
t_bool	entity_creation_is_allowed(t_entity_list **head,
		t_editor_sector *sector, t_action *action)
{
	int				i;
	t_editor_walls	*wall;

	wall = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls)
	{
		if (action->selected_wall == wall->idx && wall->type >= 0)
			return (false);
		wall = wall->next;
		i++;
	}
	if (action->create_light_button
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			light_button))
		return (false);
	if (action->create_light_source
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			lamp))
		return (false);
	if (action->create_elev_button
		&& calc_entities_in_sector_with_type(head, sector->idx_sector,
			lift_button))
		return (false);
	return (true);
}
