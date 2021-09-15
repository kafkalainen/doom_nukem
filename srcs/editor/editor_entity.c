/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:56:22 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 09:53:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		get_new_link_index(t_entity_list **list, int current_entity)
{
	int				nbr;
	int				highest;
	t_entity_list	*temp;
	t_entity_list	*link;

	nbr = 0;
	temp = *list;
	link = *list;
	while (temp != NULL && temp->entity_idx != current_entity)
	{
		if (temp->entity_idx == current_entity)
		{
			if (temp->is_linked > 1)
				nbr = temp->is_linked;
		}
		temp = temp->next;
	}
	if (nbr > 1)
		return (nbr);
	else
	{
		nbr = 0;
		highest = 2;
		while (link != NULL)
		{
			if (link->is_linked == 2)
				nbr++;
			if (link->is_linked > highest)
				highest = link->is_linked;
			link = link->next;
		}
		if (nbr == 0)
				highest = 2;
		else
			highest++;
		temp->is_linked = highest;
	}
	return (highest);
}

t_bool	link_allowed(t_entity_list *from, t_entity_list *to)
{
	if ((from->entity_type == light_button && to->entity_type == lamp) ||
 		(from->entity_type == lamp && to->entity_type == light_button))
		return (true);
	return (false);
}

t_bool	link_entities(t_entity_list **entities, t_editor_sector **sectors,
		t_xy click, int current_entity)
{
	t_entity_list	*starting_link;
	t_entity_list	*clicked_entity;
	t_editor_sector	*clicked_entity_sector;
	int				click_entity_idx;

	starting_link = get_entity_with_idx(entities, current_entity);
	clicked_entity = get_clicked_entity(entities, click, &click_entity_idx);
	if (!starting_link || !clicked_entity
		|| !link_allowed(starting_link, clicked_entity))
		return (false);
	starting_link->is_linked = clicked_entity->sector_idx + 2;
	clicked_entity->is_linked = starting_link->is_linked;
	clicked_entity_sector = get_editor_sector_with_idx(sectors,
							clicked_entity->sector_idx);
	if (!clicked_entity_sector)
		return (false);
	clicked_entity_sector->light.is_linked = starting_link->is_linked;
	clicked_entity_sector->light.state = starting_link->state;
	clicked_entity->state = starting_link->state;
	return (true);
}

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

void	delete_selected_entity(t_entity_list **head, t_action *action)
{
	t_entity_list	*temp;
	t_entity_list	*prev;

	temp = *head;
	if (!temp)
		return ;
	if (temp != NULL && temp->entity_idx == action->selected_entity)
	{
		*head = temp->next;
		free(temp);
		reset_list_indexes(head);
		action->delete = 0;
		action->selected_entity = -1;
		return ;
	}
	while (temp != NULL && temp->entity_idx != action->selected_entity)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
	reset_list_indexes(head);
	action->delete = 0;
	action->selected_entity = -1;
}

void	edit_entity(t_entity_list *entity, t_action *action, t_editor_sector *sector)
{
	if (action->change_entity_type)
	{
		if (entity->entity_type == skull_skulker)
			entity->entity_type = thing;
		else if (entity->entity_type == thing)
			entity->entity_type = drone;
		else if (entity->entity_type == drone)
			entity->entity_type = crewmember;
		else if (entity->entity_type == crewmember)
			entity->entity_type = ammo_pack;
		else if (entity->entity_type == ammo_pack)
			entity->entity_type = keycard_cleaning;
		else if (entity->entity_type == keycard_cleaning)
			entity->entity_type = keycard_engineering;
		else if (entity->entity_type == keycard_engineering)
			entity->entity_type = keycard_military;
		else if (entity->entity_type == keycard_military)
			entity->entity_type = skull_skulker;
		action->change_entity_type = 0;
	}
	else if (action->toggle_entity_is_linked)
	{
		if (entity->is_linked > 0)
			entity->is_linked = 0;
		else
			entity->is_linked = 1;
		if (entity->entity_type == lamp)
			sector->light.is_linked = entity->is_linked;
		action->toggle_entity_is_linked = 0;
	}
	else if (action->toggle_is_revealed)
	{
		if (entity->is_revealed == 0)
			entity->is_revealed = 1;
		else
			entity->is_revealed = 0;
		action->toggle_is_revealed = 0;
	}
	else if (action->toggle_state)
	{
		if (entity->state == 0)
			entity->state = 1;
		else
			entity->state = 0;
		if (entity->entity_type == lamp)
			sector->light.state = entity->state;
		action->toggle_state = 0;
	}
	action->edit_entity = 0;
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
