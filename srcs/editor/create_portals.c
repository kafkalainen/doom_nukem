/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:16:04 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/27 14:54:37 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_walls	*get_intersecting_wall(t_editor_sector *sector,
	int nbr_of_walls, t_xy dir, t_xy pos)
{
	int				i;
	int				found;
	t_editor_walls	*wall;
	t_xy			vec;
	t_xy			vec_two;

	i = 0;
	found = 0;
	wall = sector->walls;
	while (i < nbr_of_walls)
	{
		vec = vec2(wall->x0.x, wall->x0.y);
		vec_two = vec2(wall->next->x0.x, wall->next->x0.y);
		if (check_if_lseg_intersects(&vec, &vec_two, &pos, &dir))
		{
			found = 1;
			break ;
		}
		wall = wall->next;
		i++;
	}
	if (!found)
		return (NULL);
	return (wall);
}

t_editor_walls	*get_matching_wall_coord(t_editor_sector *sector,
	t_screen_xy x0, t_screen_xy x1)
{
	t_editor_walls	*wall;
	int				i;

	wall = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls)
	{
		if (wall->x0.x == x1.x && wall->x0.y == x1.y
			&& wall->next->x0.x == x0.x && wall->next->x0.y == x0.y)
			return (wall);
		wall = wall->next;
		i++;
	}
	return (NULL);
}

t_bool	create_portal_between_sectors(t_editor_sector **head, t_action *action)
{
	t_editor_sector	*link_from;
	t_editor_sector	*link_to;
	t_editor_walls	*wall;
	t_editor_walls	*wall_two;
	t_xy			dir;

	link_from = get_editor_sector_with_idx(head, action->prev_sector);
	link_to = get_editor_sector_with_idx(head, action->selected_sector);
	if (!link_from || link_from->is_elevator
		|| !link_to || link_to->is_elevator)
		return (false);
	dir = vec2_add(link_from->centroid,
			vec2_dec(action->world_pos, link_from->centroid));
	wall = get_intersecting_wall(link_from, link_from->nb_of_walls,
			dir, link_from->centroid);
	if (!wall)
		return (false);
	wall_two = get_matching_wall_coord(link_to, wall->x0, wall->next->x0);
	if (!wall_two)
		return (false);
	wall->type = link_to->idx_sector;
	wall_two->type = link_from->idx_sector;
	return (true);
}
