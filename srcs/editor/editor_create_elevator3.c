/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:40:18 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/06 16:42:34 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	set_lift_values(int *first,
	int *second, t_bool val, int idx_sector)
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
	return (idx_sector);
}

t_bool	sectors_aligned(t_editor_sector *first, t_editor_sector *second,
	t_editor_sector *lift, t_screen_xy heights)
{
	if (heights.x < heights.y)
	{
		lift->is_elevator = set_lift_values(&first->is_elevator,
				&second->is_elevator, true, second->idx_sector);
		return (true);
	}
	else if (heights.y < heights.x)
	{
		lift->is_elevator = set_lift_values(&first->is_elevator,
				&second->is_elevator, false, first->idx_sector);
		return (true);
	}
	return (false);
}

t_bool	lower_portal_at_correct_floor_height(t_editor_walls *first,
	t_editor_walls *second, t_editor_sector *sector, t_screen_xy *heights)
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
			&& first->height.ground > second->height.ground)
		|| (second->height.ground == second->height.ground
			&& first->height.ground != wall_one->height.ground
			&& second->height.ground > first->height.ground))
		return (false);
	(*heights).x = first->height.ground;
	(*heights).y = second->height.ground;
	return (true);
}
