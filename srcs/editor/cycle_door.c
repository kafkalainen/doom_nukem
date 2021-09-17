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
	selected->type = opposite_idx;
	opposite->type = idx;
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

static	void	inflate_idx(int *inflatable, int *amount)
{
	if (*amount > 11999)
		*inflatable += MILITARY_INDEX;
	else if (*amount > 8999)
		*inflatable += ENGINEERING_INDEX;
	else if (*amount > 5999)
		*inflatable += CLEANING_INDEX;
	else if (*amount > 2999)
		*inflatable += DOOR_INDEX;	
}

t_bool	cycle_door(t_editor_sector **sector_list, t_editor_walls *selected, int idx)
{
	int 			opposite;
	int				inflated_idx;
	t_editor_sector *sector;

	if (!sector_list && !selected)
		error_output("sector_list and|or selected wall is null");
	opposite = selected->type;
	inflate_idx(&idx, &opposite);
	inflated_idx = idx;
	normalize_idx(&idx, &opposite);
	sector = *sector_list;
	while (sector->idx_sector != opposite && sector->next)
		sector = sector->next;
	while (sector->walls->type != inflated_idx)
		sector->walls = sector->walls->next;
	if (inflated_idx >= MILITARY_INDEX)
		assign_portal_type(selected, sector->walls, idx, opposite);
	else if (selected->type >= 0)
	{
		inflate_idx(&opposite, &inflated_idx);
		assign_portal_type(selected, sector->walls, (inflated_idx + DOOR_INDEX),
			(opposite + DOOR_INDEX));
	}
	return (false);	
}