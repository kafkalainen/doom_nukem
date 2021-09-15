/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_delete_entity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:34:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 15:05:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	delete_selected_entity(t_entity_list **head, t_action *action)
{
	t_entity_list	*temp;
	t_entity_list	*prev;

	if (!*head)
		return ;
	temp = *head;
	if (temp != NULL && temp->entity_idx == action->selected_entity)
	{
		*head = temp->next;
		free(temp);
		reset_list_indexes(head);
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
}

void	delete_entity_with_idx(t_entity_list **head, int idx)
{
	t_entity_list	*temp;
	t_entity_list	*prev;

	temp = *head;
	if (!temp)
		return ;
	if (temp != NULL && temp->entity_idx == idx)
	{
		*head = temp->next;
		free(temp);
		reset_list_indexes(head);
		return ;
	}
	while (temp != NULL && temp->entity_idx != idx)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
	reset_list_indexes(head);
}

void	delete_entities_from_sector(t_entity_list **entity_head, int sector_idx)
{
	t_entity_list	*temp;

	temp = *entity_head;
	while (temp != NULL)
	{
		if (temp->sector_idx == sector_idx)
			delete_entity_with_idx(entity_head, temp->entity_idx);
		temp = temp->next;
	}
}
