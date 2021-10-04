/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:13:03 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/04 12:40:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	reset_elevator_values(t_editor_sector *sector,
	t_editor_sector **sectors, t_entity_list **entity_head)
{
	if (!sector)
		return (false);
	if (!check_nbr_of_portals(&sector->walls, sector->nb_of_walls))
		return (false);
	if (!check_for_elevator_button(entity_head, sector->idx_sector))
		return (false);
	if (!verify_connecting_sectors(sectors, sector))
		return (false);
	return (true);
}

void	reset_elevators(t_editor_sector **head, t_entity_list **entity_head)
{
	t_editor_sector	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->is_elevator)
		{
			if (reset_elevator_values(temp, head, entity_head))
				convert_sector_to_lift(temp, entity_head);
		}
		temp = temp->next;
	}
}
