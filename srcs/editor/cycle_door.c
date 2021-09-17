/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparviai <eparviai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:21:22 by eparviai          #+#    #+#             */
/*   Updated: 2021/09/17 15:57:48 by eparviai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	assign_portal_type(t_editor_walls *selected, t_editor_walls *opposite, int idx, int opposite_idx)
{
	selected->type = idx;
	opposite->type = opposite_idx;
	printf("%d idx in assgn portal\n", opposite_idx);
}

static void	normalize_idx(int *idx, int *opposite)
{
	if (*idx > 11999)
		*idx -= MILITARY_INDEX;
	else if (*idx > 8999)
		*idx -= ENGINEERING_INDEX;
	else if (*idx > 5999)
		*idx -= CLEANING_INDEX;
	else if (*idx > 2999)
		*idx -= DOOR_INDEX;
	if (*opposite > 11999)
		*opposite -= MILITARY_INDEX;
	else if (*opposite > 8999)
		*opposite -= ENGINEERING_INDEX;
	else if (*opposite > 5999)
		*opposite -= CLEANING_INDEX;
	else if (*opposite > 2999)
		*opposite -= DOOR_INDEX;	
}

t_bool	cycle_door(t_editor_sector *sector_list, t_editor_walls *selected, int idx)
{
	int 			opposite;
	t_editor_sector *sector;

	opposite = selected->type;
	printf("in cycle_door idx value %d\n", opposite);
	normalize_idx(&idx, &opposite);
	sector = get_editor_sector_with_idx(&sector_list, opposite);
	printf("%d selected type 	opposite type %d \n", selected->type, sector->walls->type);
	while (sector->walls->type != idx)
		sector->walls = sector->walls->next;
	if (selected->type > 11999)
		assign_portal_type(selected, sector->walls, idx, opposite);
	else if (selected->type >= 0)
		assign_portal_type(selected, sector->walls, (idx + DOOR_INDEX),
			(opposite + DOOR_INDEX));
	return (false);	
}