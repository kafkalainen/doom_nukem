/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:56:22 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/22 17:26:05 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_highest_floor_height(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				i;
	int				highest;

	highest = -99;
	i = 0;
	temp = *walls;
	while (temp != NULL && i < nbr_of_walls)
	{
		if (temp->height.ground > highest)
			highest = temp->height.ground;
		temp = temp->next;
		i++;
	}
	return (highest + 1);
}

int	get_selected_floor_height(t_editor_sector *sector, int wall_idx)
{
	t_editor_walls	*temp;
	int				i;

	temp = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls && temp->idx != wall_idx)
		temp = temp->next;
	if (!temp)
		error_output("Wall is null pointer\n");
	return (temp->height.ground);
}

void	get_midpoint_of_walls(t_editor_sector *sector,
	int wall_idx, int *x, int *y)
{
	t_editor_walls	*temp;
	t_xy			midpoint;
	int				i;

	temp = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls && temp->idx != wall_idx)
		temp = temp->next;
	if (!temp)
		error_output("Wall is null pointer\n");
	if (temp->x0.x < temp->next->x0.x)
		midpoint.x = (temp->next->x0.x + temp->x0.x) * 0.5;
	else
		midpoint.x = (temp->x0.x + temp->next->x0.x) * 0.5;
	if (temp->x0.y < temp->next->x0.y)
		midpoint.y = (temp->next->x0.y + temp->x0.y) * 0.5;
	else
		midpoint.y = (temp->x0.y + temp->next->x0.y) * 0.5;
	midpoint.w = 0.0f;
	*x = midpoint.x;
	*y = midpoint.y;
}

void	get_direction_from_wall(t_entity_list *new,
	t_editor_sector *sector, int wall_idx)
{
	t_editor_walls	*temp;
	int				i;
	t_xy			norm;

	temp = sector->walls;
	i = 0;
	while (i < sector->nb_of_walls && temp->idx != wall_idx)
		temp = temp->next;
	if (!temp)
		error_output("Wall is null pointer\n");
	norm = vec2_normal(vec2(temp->x0.x, temp->x0.y),
			vec2(temp->next->x0.x, temp->next->x0.y));
	new->dir.x = norm.x;
	new->dir.z = norm.y;
	new->dir.y = 0;
}

int	get_lowest_ceiling_height(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*wall;
	int				i;
	int				ceiling_height;

	i = 0;
	wall = *walls;
	ceiling_height = wall->height.ceiling;
	while (i < nbr_of_walls)
	{
		if (ceiling_height < wall->height.ceiling)
			ceiling_height = wall->height.ceiling;
		i++;
		wall = wall->next;
	}
	return (ceiling_height);
}
