/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_entity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:28:41 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/21 15:05:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	create_new_entity(t_entity_list **head, t_action *action,
	t_editor_sector *sector, t_xy pos)
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

void	init_non_static_entity(t_entity_list *new,
	t_editor_sector *sector, t_xy pos)
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

void	initialize_entity_data(t_entity_list *new, t_action *action,
	t_editor_sector *sector, t_xy pos)
{
	if (action->create_elev_button || action->create_light_button
		|| action->create_powerstation || action->create_light_source)
		init_static_entity(new, action, sector, pos);
	else
		init_non_static_entity(new, sector, pos);
	new->bbox.start = vec2(new->pos.x - 0.2f, new->pos.z + 0.2f);
	new->bbox.end = vec2(new->pos.x + 0.2f, new->pos.z - 0.2f);
	new->entity_idx = 0;
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
