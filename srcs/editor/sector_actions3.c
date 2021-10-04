/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:13:03 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/04 14:30:33 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*check_for_neighboring_connections(t_editor_sector *sector,
	t_editor_sector **head, int sector_idx)
{
	int				i;
	t_editor_walls	*wall;
	t_editor_sector	*temp;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type >= 0 && wall->type != sector_idx)
		{
			temp = get_editor_sector_with_idx(head, get_portal_idx(wall->type));
			if (temp && temp->is_elevator)
				return (temp);
		}
		wall = wall->next;
		i++;
	}
	return (NULL);
}

void	reset_connecting_sectors(t_editor_sector *sector,
	t_editor_sector **head, int sector_idx)
{
	int				i;
	t_editor_walls	*wall;
	t_editor_sector	*temp;
	t_editor_sector	*temp_two;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type >= 0 && wall->type != sector_idx)
		{
			temp = get_editor_sector_with_idx(head, get_portal_idx(wall->type));
			if (temp && temp->is_elevator)
			{
				temp_two = check_for_neighboring_connections(temp,
						head, temp->idx_sector);
				if (temp_two)
					temp_two->is_elevator = 0;
				temp->is_elevator = 0;
			}	
		}
		wall = wall->next;
		i++;
	}
}

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
