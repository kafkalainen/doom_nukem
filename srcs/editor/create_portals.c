/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:16:04 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 16:09:55 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	create_portal_between_sectors(t_editor_sector **head, t_action *action)
{
	t_editor_sector	*link_from;
	t_editor_sector	*link_to;
	t_editor_walls	*wall_one;
	t_editor_walls	*wall_two;
	t_xy			vec;
	t_xy			vec_two;
	t_xy			dir;
	int				i;
	int				found;
	int				nbr_of_walls;

	link_from = *head;
	link_to = *head;
	while (link_from != NULL && link_from->idx_sector != action->prev_sector)
		link_from = link_from->next;
	if (!link_from || link_from->is_elevator)
		return ;
	while (link_to != NULL && link_to->idx_sector != action->selected_sector)
		link_to = link_to->next;
	if (!link_to || link_to->is_elevator)
		return ;
	i = 0;
	found = 0;
	nbr_of_walls = link_from->nb_of_walls;
	wall_one = link_from->walls;
	dir = vec2_add(link_from->centroid, vec2_dec(link_to->centroid, link_from->centroid));
	while (i < nbr_of_walls)
	{
		vec = vec2(wall_one->x0.x, wall_one->x0.y);
		vec_two = vec2(wall_one->next->x0.x, wall_one->next->x0.y);
		if (check_if_lseg_intersects(&vec, &vec_two, &link_from->centroid, &dir))
		{
			found = 1;
			break ;
		}
		wall_one = wall_one->next;
		i++;
	}
	if (!found)
		return ;
	i = 0;
	wall_two = link_to->walls;
	nbr_of_walls = link_to->nb_of_walls;
	found = 0;
	dir = vec2_add(link_to->centroid, vec2_dec(link_from->centroid, link_to->centroid));
	while (i < nbr_of_walls)
	{
		vec = vec2(wall_two->x0.x, wall_two->x0.y);
		vec_two = vec2(wall_two->next->x0.x, wall_two->next->x0.y);
		if (check_if_lseg_intersects(&vec, &vec_two, &link_to->centroid, &dir))
		{
			found = 1;
			break ;
		}
		wall_two = wall_two->next;
		i++;
	}
	if (!found)
		return ;
	wall_one->type = link_to->idx_sector;
	wall_two->type = link_from->idx_sector;
}
