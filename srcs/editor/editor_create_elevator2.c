/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_elevator2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:14:52 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/05 14:57:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_nbr_of_portals(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*wall;
	int				i;
	int				nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	wall = *walls;
	while (i < nbr_of_walls)
	{
		if (wall->type >= 0)
			nbr_of_portals++;
		i++;
		wall = wall->next;
	}
	if (nbr_of_portals != 2)
		return (false);
	return (true);
}

t_bool	check_for_elevator_button(t_entity_list **head, int sector_idx)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector_idx
			&& temp->type == lift_button)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (false);
	return (true);
}

void	get_lowest_floor(t_editor_sector *sector, int *height)
{
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	*height = wall->height.ground;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ground < *height)
			*height = wall->height.ground;
		i++;
		wall = wall->next;
	}
}

void	get_connecting_sectors(t_editor_walls *wall, int *first_sector_idx,
	int *second_sector_idx, int nbr_of_walls)
{
	int	i;
	int	nbr_of_portals;

	i = 0;
	nbr_of_portals = 0;
	while (i < nbr_of_walls)
	{
		if (wall->type >= 0)
		{
			nbr_of_portals++;
			if (nbr_of_portals == 1)
				*first_sector_idx = wall->type;
			else
				*second_sector_idx = wall->type;
		}
		i++;
		wall = wall->next;
	}
	if (*first_sector_idx < 0 || *second_sector_idx < 0)
	{
		*first_sector_idx = -1;
		*second_sector_idx = -1;
	}
}
