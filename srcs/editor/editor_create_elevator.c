/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:11:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/20 13:29:14 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	sectors_aligned(t_editor_sector *first, t_editor_sector *second,
		t_screen_xy heights, t_editor_sector *elev_sector)
{
	int	lift_height;

	get_lowest_floor(elev_sector, &lift_height);
	if (heights.x == heights.y)
		return (false);
	if (lift_height == heights.x)
	{
		first->is_elevator = lower;
		second->is_elevator = upper;
		elev_sector->is_elevator = second->idx_sector;
		return (true);
	}
	else if (lift_height == heights.y)
	{
		first->is_elevator = upper;
		second->is_elevator = lower;
		elev_sector->is_elevator = first->idx_sector;
		return (true);
	}
	return (false);
}

t_bool	compare_floors_to_ceilings(t_editor_sector **sectors, int first_idx,
		int second_idx, t_editor_sector *elev_sector)
{
	t_editor_sector	*first;
	t_editor_sector	*second;
	t_screen_xy		floor_heights;

	first = *sectors;
	second = *sectors;
	while (first)
	{
		if (first->idx_sector == first_idx)
			break ;
		first = first->next;
	}
	if (!first)
		return (false);
	while (second)
	{
		if (second->idx_sector == second_idx)
			break ;
		second = second->next;
	}
	if (!second)
		return (false);
	get_lowest_floor(first, &floor_heights.x);
	get_lowest_floor(second, &floor_heights.y);
	return (sectors_aligned(first, second, floor_heights, elev_sector));
}

t_bool	verify_connecting_sectors(t_editor_sector **sectors,
		t_editor_sector *elev_sector)
{
	int	first_sector_idx;
	int	scdn_sector_idx;

	scdn_sector_idx = -1;
	first_sector_idx = -1;
	get_connecting_sectors(elev_sector->walls, &first_sector_idx,
		&scdn_sector_idx, elev_sector->nb_of_walls);
	if (!compare_floors_to_ceilings(sectors, first_sector_idx,
			scdn_sector_idx, elev_sector))
		return (false);
	return (true);
}

t_bool	check_elevator_prerequisites(t_entity_list **head,
		t_editor_sector **sectors, t_action *action)
{
	t_editor_sector	*sector;

	sector = *sectors;
	while (sector)
	{
		if (sector->idx_sector == action->selected_sector)
			break ;
		sector = sector->next;
	}
	if (!sector)
		return (false);
	if (!check_nbr_of_portals(&sector->walls, sector->nb_of_walls))
		return (false);
	if (!check_for_elevator_button(head, sector->idx_sector))
		return (false);
	if (!verify_connecting_sectors(sectors, sector))
		return (false);
	return (true);
}

void	convert_sector_to_lift(t_editor_sector *sector,
		t_entity_list **head)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector->idx_sector
			&& temp->entity_type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return ;
	temp->is_linked = sector->idx_sector + 2;
	sector->is_elevator = lift;
}
