/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:56:22 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/08 17:08:13 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*get_clicked_entity(t_entity_list **list, t_screen_xy mdata, int *selected_entity)
{
	t_entity_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, mdata.x, mdata.y))
		{
			*selected_entity = temp->entity_idx;
			return (temp);
		}
		temp = temp->next;
	}
	*selected_entity = -1;
	return (NULL);
}

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

int	link_allowed(t_entity_list *entity1, t_entity_list *entity2)
{
	if ((entity1->entity_type == light_button && entity2->entity_type == lamp) ||
 		(entity2->entity_type == light_button && entity1->entity_type == lamp))
		return (TRUE);
	return (FALSE);
}

int	link_entities(t_entity_list **list, t_mouse_data mdata, int current_entity)
{
	t_entity_list	*temp;
	t_entity_list	*curr;
	int				link_nbr;

	temp = *list;
	curr = *list;
	while (curr != NULL && curr->entity_idx != current_entity)
		curr = curr->next;
	if (!curr)
		return (FALSE);
	// while (temp != NULL && !check_entity_bbox(temp->bbox, mdata))
	// 	temp = temp->next;
	// if (!temp)
	// 	return (FALSE);
	// if (link_allowed(curr, temp))
	// {

	// }
	if (curr && curr->is_linked > 1)
		link_nbr = curr->is_linked;
	else
		link_nbr = get_new_link_index(list, current_entity);
	while (temp != NULL)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end, mdata.x, mdata.y))
		{
			if (temp->is_linked < 2)
				temp->is_linked = link_nbr;
			else
				curr->is_linked = temp->is_linked;
			return (TRUE);
		}
		temp = temp->next;
	}
	return (FALSE);
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

void	delete_entity(t_entity_list **head, t_action *action)
{
	t_entity_list	*temp;
	t_entity_list	*prev;

	temp = *head;
	if (temp == NULL)
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

void	edit_entity(t_entity_list *entity, t_action *action)
{
	if (action->change_entity_type)
	{
		if ((entity->entity_type >= 0 && entity->entity_type < 4) || entity->entity_type == lamp)
		{
			if (entity->entity_type < 3)
				entity->entity_type += 1;
			else if (entity->entity_type == 3)
				entity->entity_type = lamp;
			else if (entity->entity_type == lamp)
				entity->entity_type = skull_skulker;
			else if (entity->entity_type == light_button || entity->entity_type == powerstation)
			{
				if (entity->entity_type == light_button)
					entity->entity_type = powerstation;
				else
					entity->entity_type = light_button;
			}
		}
		action->change_entity_type = 0;
	}
	else if (action->toggle_entity_is_linked)
	{
		if (entity->is_linked > 0)
			entity->is_linked = 0;
		else
			entity->is_linked = 1;
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
	else if (action->toggle_is_static)
	{
		if (entity->is_static == 0)
			entity->is_static = 1;
		else
			entity->is_static = 0;
		action->toggle_is_static = 0;
	}
	else if (action->toggle_state)
	{
		if (entity->state == 0)
			entity->state = 1;
		else
			entity->state = 0;
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
	return (highest);
}

// void	get_direction_from_wall_points(t_editor_xyz *dir, t_editor_walls **walls, int nbr_of_walls, int selected_wall)
// {
// 	t_editor_walls	*temp;
// 	int				i;

// 	i = 0;
// 	temp = *walls;
// 	while (temp != NULL && i < nbr_of_walls)
// 	{
// 		if (temp->idx == selected_wall)
// 		{

// 		}
// 		i++;
// 		temp = temp->next;
// 	}
// }

void	create_new_entity(t_entity_list **head, t_mouse_data *mdata, t_action *action, t_sector_list *sector)
{
	t_entity_list	*temp;
	t_entity_list	*new;

	// if (sector == NULL)
	// 	return ;
	(void)sector;
	new = (t_entity_list *)malloc(sizeof(t_entity_list));
	if (!new)
		error_output("Memory allocation of new entity failed\n");
	if (action->create_elev_button)
		new->entity_type = lift_button;
	else if (action->create_light_button)
		new->entity_type = light_button;
	else if (action->create_powerstation)
		new->entity_type = powerstation;
	else
		new->entity_type = skull_skulker;
	new->is_active = 0;
	new->is_linked = 0;
	new->is_revealed = 0;
	new->is_static = 0;
	new->sector_idx = 0; //sector->idx_sector;
	new->pos.x = (mdata->x - action->offset.x) / action->scalar;
	new->pos.z = (mdata->y - action->offset.y) / action->scalar;
	new->bbox.start = vec2(new->pos.x - 1, new->pos.z - 1);
	new->bbox.end = vec2((new->pos.x + 1), (new->pos.z + 1));
	new->pos.y = 0; //get_highest_floor_height(&sector->walls, sector->nb_of_walls); // need to calculate height difference between sector floor and entity height
	// if (new->entity_type == elevator_button || new->entity_type == light_button || new->entity_type == powerstation)
	// 	get_direction_from_wall_point(&new->dir, &sector->walls, sector->nb_of_walls, action->selected_wall);
	// else
	// {
		new->dir.x = 0;
		new->dir.y = 1;
		new->dir.z = 0;
	// }
	new->state = 0;
	new->entity_idx = 0;
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
	printf("entity idx: %i, ent pos x: %i, y: %i\n", new->entity_idx, new->pos.x, new->pos.z);
}
