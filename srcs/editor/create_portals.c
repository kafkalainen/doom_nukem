/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:16:04 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/11 15:15:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	create_portal_between_sectors(t_editor_sector **head, t_action *action)
{
	t_editor_sector	*link_from;
	t_editor_sector	*link_to;
	t_editor_walls	*temp_wall;
	// t_editor_walls	*temp_wall_two;
	int				i;
	int				nbr_of_walls;

	link_from = *head;
	link_to = *head;
	
	while (link_from != NULL && link_from->idx_sector != action->prev_sector)
		link_from = link_from->next;
	if (!link_from)
		return ;
	while (link_to != NULL && link_to->idx_sector != action->selected_sector)
		link_to = link_to->next;
	if (!link_to)
		return ;
	i = 0;
	nbr_of_walls = link_from->nb_of_walls;
	temp_wall = link_from->walls;
	// temp_wall_two = temp_wall->next;
	while (i < nbr_of_walls)
	{
		temp_wall = temp_wall->next;
		// temp_wall_two = temp_wall->next;
		i++;
	}
}
