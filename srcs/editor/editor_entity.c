/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:56:22 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 15:03:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	reset_list_indexes(t_entity_list **head)
{
	t_entity_list	*temp;
	int				idx;
	int				nbr_of_entities;

	nbr_of_entities = get_entity_count(head);
	temp = *head;
	idx = 0;
	while (idx < nbr_of_entities)
	{
		temp->entity_idx = idx;
		temp = temp->next;
		idx++;
	}
}

int		get_highest_floor_height(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				i;
	int				highest;

	highest = 0;
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

void	get_midpoint_of_walls(t_editor_sector *sector, int wall_idx, int *x, int *y)
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

void	get_direction_from_wall(t_entity_list *new, t_editor_sector *sector, int wall_idx)
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
	norm = vec2_normal(vec2(temp->x0.x, temp->x0.y),vec2(temp->next->x0.x, temp->next->x0.y));
	new->dir.x = norm.x;
	new->dir.z = norm.y;
	new->dir.y = 0;
}

int		get_lowest_ceiling_height(t_editor_walls **walls, int nbr_of_walls)
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

void	init_static_entity(t_entity_list *new, t_action *action, t_editor_sector *sector, t_xy pos)
{
	if (action->create_elev_button)
		new->entity_type = lift_button;
	else if (action->create_light_button)
		new->entity_type = light_button;
	else if (action->create_powerstation)
		new->entity_type = powerstation;
	else
		new->entity_type = lamp;
	new->is_active = true;
	new->is_linked = 0;
	new->is_revealed = 0;
	new->is_static = true;
	new->state = true;
	new->sector_idx = sector->idx_sector;
	if (action->create_elev_button || action->create_light_button ||
		action->create_powerstation)
	{
		get_midpoint_of_walls(sector, action->selected_wall, &new->pos.x, &new->pos.z);
		new->pos.y = get_selected_floor_height(sector, action->selected_wall) + 1;
		get_direction_from_wall(new, sector, action->selected_wall);
	}
	else
	{
		new->pos.x = pos.x;
		new->pos.z = pos.y;
		new->pos.y = get_lowest_ceiling_height(&sector->walls, sector->nb_of_walls);
		new->dir.x = 0;
		new->dir.y = -1;
		new->dir.z = 0;
	}
	new->is_static = 1;
}

void	init_non_static_entity(t_entity_list *new, t_editor_sector *sector, t_xy pos)
{
	new->entity_type = skull_skulker;
	new->is_active = true;
	new->is_linked = false;
	new->is_revealed = false;
	new->is_static = false;
	new->sector_idx = sector->idx_sector;
	new->state = false;
	new->pos.x = ft_roundf_to_grid(pos.x, 0);
	new->pos.z = ft_roundf_to_grid(pos.y, 0);
	new->pos.y = get_highest_floor_height(&sector->walls, sector->nb_of_walls);
	new->dir.x = 0;
	new->dir.y = 0;
	new->dir.z = -1;
}

void	initialize_entity_data(t_entity_list *new, t_action *action, t_editor_sector *sector, t_xy pos)
{
	if (action->create_elev_button || action->create_light_button ||
		action->create_powerstation || action->create_light_source)
		init_static_entity(new, action, sector, pos);
	else
		init_non_static_entity(new, sector, pos);
	new->bbox.start = vec2(new->pos.x - 0.2f, new->pos.z + 0.2f);
	new->bbox.end = vec2(new->pos.x + 0.2f, new->pos.z - 0.2f);
	new->entity_idx = 0;
}

void	create_new_entity(t_entity_list **head, t_action *action, t_editor_sector *sector, t_xy pos)
{
	t_entity_list	*temp;
	t_entity_list	*new;

	if (sector == NULL)
		return ;
	new = (t_entity_list *)malloc(sizeof(t_entity_list));
	if (!new)
		error_output("Memory allocation of new entity failed\n");
	initialize_entity_data(new, action, sector, pos);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			new->entity_idx++;
			temp = temp->next;
		}
		new->entity_idx++;
		temp->next = new;
		new->next = NULL;
	}
}
