/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:40:18 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/06 18:42:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_lift_values(int *first, int *second, t_bool val)
{
	if (val)
	{
		*first = lower;
		*second = upper;
	}
	else
	{
		*first = upper;
		*second = lower;
	}
}

t_bool	which_is_lower(t_editor_walls *first,
	t_editor_walls *second, t_editor_sector *lift, int *ret)
{
	t_editor_walls	*wall_one;
	t_editor_walls	*wall_two;

	wall_one = get_matching_wall_coord(lift, first->x0, first->next->x0);
	wall_two = get_matching_wall_coord(lift, second->x0, second->next->x0);
	if (!wall_one || !wall_two)
		return (false);
	if (wall_one->height.ground == first->height.ground)
	{
		*ret = 1;
		return (true);
	}
	else if (wall_two->height.ground == second->height.ground)
	{
		*ret = 0;
		return (true);
	}
	return (false);
}

t_bool	sectors_aligned(t_editor_sector *first, t_editor_sector *second,
	t_editor_sector *lift)
{
	t_editor_walls	*wall_one;
	t_editor_walls	*wall_two;
	int				ret;

	wall_one = get_editor_wall_with_type(&first->walls,
			first->nb_of_walls, lift->idx_sector);
	wall_two = get_editor_wall_with_type(&second->walls,
			second->nb_of_walls, lift->idx_sector);
	if (!wall_one || !wall_two)
		return (false);
	ret = -1;
	if (!which_is_lower(wall_one, wall_two, lift, &ret))
		return (false);
	if (ret == 1)
	{
		set_lift_values(&first->is_elevator, &second->is_elevator, true);
		return (true);
	}
	else if (ret == 0)
	{
		set_lift_values(&first->is_elevator, &second->is_elevator, false);
		return (true);
	}
	return (false);
}

t_bool	lower_portal_at_correct_floor_height(t_editor_walls *first,
	t_editor_walls *second, t_editor_sector *sector)
{
	t_editor_walls	*wall_one;
	t_editor_walls	*wall_two;

	wall_one = get_matching_wall_coord(sector, first->x0, first->next->x0);
	wall_two = get_matching_wall_coord(sector, second->x0, second->next->x0);
	if (!wall_one || !wall_two)
		return (false);
	if (wall_one->height.ground != first->height.ground
		&& wall_two->height.ground != second->height.ground)
		return (false);
	if ((first->height.ground == wall_one->height.ground
			&& wall_two->height.ground != second->height.ground
			&& first->height.ground == second->height.ground)
		|| (second->height.ground == second->height.ground
			&& first->height.ground != wall_one->height.ground
			&& second->height.ground == first->height.ground))
		return (false);
	return (true);
}
