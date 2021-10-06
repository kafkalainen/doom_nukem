/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:11:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/06 18:18:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	compare_floors_to_ceilings(t_editor_sector *first,
	t_editor_sector *second, t_editor_sector *elev_sector)
{
	t_editor_walls	*first_wall;
	t_editor_walls	*second_wall;

	if (!first || !second || !elev_sector)
		return (false);
	first_wall = get_editor_wall_with_type(&first->walls,
			first->nb_of_walls, elev_sector->idx_sector);
	second_wall = get_editor_wall_with_type(&second->walls,
			second->nb_of_walls, elev_sector->idx_sector);
	if (!first_wall || !second_wall)
		return (false);
	if (!lower_portal_at_correct_floor_height(first_wall,
			second_wall, elev_sector))
		return (false);
	return (sectors_aligned(first, second, elev_sector));
}

t_bool	verify_connecting_sectors(t_editor_sector **sectors,
		t_editor_sector *elev_sector)
{
	t_editor_sector	*first;
	t_editor_sector	*second;

	first = NULL;
	second = NULL;
	if (!get_connecting_sectors(elev_sector, &first, &second, sectors))
		return (false);
	if (!first || !second)
		return (false);
	if (!compare_floors_to_ceilings(first, second, elev_sector))
		return (false);
	return (true);
}

t_bool	acceptable_height_diff(t_editor_walls *wall_one,
	t_editor_walls *wall_two)
{
	int	height;
	int	height_two;

	height = ft_abs(wall_one->height.ceiling - wall_one->height.ground);
	height_two = ft_abs(wall_two->height.ceiling - wall_two->height.ground);
	if (height > 4 || height_two > 4
		|| height < 2 || height_two < 2)
		return (false);
	if (height != height_two)
		return (false);
	return (true);
}

t_bool	check_lift_conditions(t_editor *editor)
{
	if (!editor->temp_sector)
		return (false);
	if (!check_nbr_of_portals(&editor->temp_sector->walls,
			editor->temp_sector->nb_of_walls))
		return (false);
	if (!check_portal_dimensions(editor))
		return (false);
	if (!check_for_elevator_button(&editor->entity_list,
			editor->temp_sector->idx_sector))
		return (false);
	if (!verify_connecting_sectors(&editor->sector_list, editor->temp_sector))
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
			&& temp->type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return ;
	temp->is_linked = sector->idx_sector + 2;
	sector->is_elevator = lift;
}
