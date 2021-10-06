/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:14:52 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/06 18:44:48 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_nbr_of_portals(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*wall;
	int				i;
	int				nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	wall = *walls;
	while (i < nbr_of_walls)
	{
		if (wall->type >= 0)
			nbr_of_portals++;
		i++;
		wall = wall->next;
	}
	if (nbr_of_portals != 2)
		return (false);
	return (true);
}

t_bool	check_for_elevator_button(t_entity_list **head, int sector_idx)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector_idx
			&& temp->type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (false);
	return (true);
}

t_bool	get_connecting_sectors(t_editor_sector *curr,
	t_editor_sector **first, t_editor_sector **second, t_editor_sector **head)
{
	t_editor_walls	*wall;
	int				i;
	int				nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	wall = curr->walls;
	while (i < curr->nb_of_walls)
	{
		if (wall->type >= 0)
		{
			nbr_of_portals++;
			if (nbr_of_portals == 1)
				*first = get_editor_sector_with_idx(head, wall->type);
			else
				*second = get_editor_sector_with_idx(head, wall->type);
		}
		i++;
		wall = wall->next;
	}
	if (!(*first) || !(*second))
		return (false);
	return (true);
}

// t_bool	evaluate_connecting_portals(t_editor_sector *next, )

t_bool	check_portal_dimensions(t_editor *editor)
{
	int				i;
	t_editor_walls	*wall;
	t_editor_sector	*temp;
	t_editor_walls	*temp_wall;

	i = 0;
	wall = editor->temp_sector->walls;
	while (i < editor->temp_sector->nb_of_walls)
	{
		if (wall->type >= 0)
		{
			temp = get_editor_sector_with_idx(&editor->sector_list,
					wall->type);
			if (!temp)
				return (false);
			temp_wall = get_editor_wall_with_type(&temp->walls,
					temp->nb_of_walls, editor->temp_sector->idx_sector);
			if (!temp_wall)
				return (false);
			if (check_if_slanted_doorway(wall, temp_wall)
				|| !acceptable_height_diff(wall, temp_wall))
				return (false);
		}
		wall = wall->next;
		i++;
	}
	return (true);
}
