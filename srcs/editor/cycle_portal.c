/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:21:22 by eparviai          #+#    #+#             */
/*   Updated: 2021/10/02 13:21:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_portal_idx(int idx)
{
	if (idx > 20999)
		idx -= LARGE_WINDOW_INDEX;
	else if (idx > 17999)
		idx -= SMALL_WINDOW_INDEX;
	else if (idx > 14999)
		idx -= SECRET_INDEX;
	else if (idx > 11999)
		idx -= MILITARY_INDEX;
	else if (idx > 8999)
		idx -= ENGINEERING_INDEX;
	else if (idx > 5999)
		idx -= CLEANING_INDEX;
	else if (idx > 2999)
		idx -= DOOR_INDEX;
	return (idx);
}

static void	assign_portal_type(t_editor_walls *selected,
	t_editor_walls *opposite, int idx, int opposite_idx)
{
	selected->type = opposite_idx;
	opposite->type = idx;
}

static void	normalize_idx(int *idx)
{
	if (*idx > 20999)
		*idx -= LARGE_WINDOW_INDEX;
	else if (*idx > 17999)
		*idx -= SMALL_WINDOW_INDEX;
	else if (*idx > 14999)
		*idx -= SECRET_INDEX;
	else if (*idx > 11999)
		*idx -= MILITARY_INDEX;
	else if (*idx > 8999)
		*idx -= ENGINEERING_INDEX;
	else if (*idx > 5999)
		*idx -= CLEANING_INDEX;
	else if (*idx > 2999)
		*idx -= DOOR_INDEX;
}

static	void	inflate_idx(int *inflatable, int *amount)
{
	if (*amount > 20999)
		*inflatable += LARGE_WINDOW_INDEX;
	else if (*amount > 17999)
		*inflatable += SMALL_WINDOW_INDEX;
	else if (*amount > 14999)
		*inflatable += SECRET_INDEX;
	else if (*amount > 11999)
		*inflatable += MILITARY_INDEX;
	else if (*amount > 8999)
		*inflatable += ENGINEERING_INDEX;
	else if (*amount > 5999)
		*inflatable += CLEANING_INDEX;
	else if (*amount > 2999)
		*inflatable += DOOR_INDEX;
}

t_bool	cycle_portal(t_editor_sector **sector_list,
	t_editor_walls *selected, int idx)
{
	int				opposite;
	int				inflated_idx;
	t_editor_sector	*sector;

	if (!sector_list && !selected)
		error_output("sector_list and|or selected wall is null");
	opposite = selected->type;
	inflate_idx(&idx, &opposite);
	inflated_idx = idx;
	normalize_idx(&idx);
	normalize_idx(&opposite);
	sector = *sector_list;
	while (sector->idx_sector != opposite && sector->next)
		sector = sector->next;
	while (sector->walls->type != inflated_idx)
		sector->walls = sector->walls->next;
	if (inflated_idx >= LARGE_WINDOW_INDEX)
		assign_portal_type(selected, sector->walls, idx, opposite);
	else if (selected->type >= 0)
	{
		inflate_idx(&opposite, &inflated_idx);
		assign_portal_type(selected, sector->walls, (inflated_idx + DOOR_INDEX),
			(opposite + DOOR_INDEX));
	}
	return (false);
}
