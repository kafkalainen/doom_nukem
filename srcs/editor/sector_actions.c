/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:51:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 15:41:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_free_walls(t_editor_walls **head, int nbr_of_walls)
{
	t_editor_walls	*item;

	while (nbr_of_walls--)
	{
		item = *head;
		*head = item->next;
		free(item);
		item = NULL;
	}
}

int	editor_new_sector_wallpoints(t_editor *editor,
	t_mouse_data *mouse_data, t_action *action)
{
	t_editor_sector	*temp;

	temp = editor->sector_list;
	while (temp != NULL && temp->idx_sector != action->selected_sector)
		temp = temp->next;
	if (mouse_data->i_mbright)
	{
		editor_remove_last_wall(temp);
		mouse_data->i_mbright = 0;
		return (0);
	}
	if (mouse_data->i_mbleft)
	{
		if (add_point_to_list(editor, temp, action) == 3)
		{
			action->delete = true;
			action->create_sector = idle;
			return (1);
		}
	}
	mouse_data->i_mbleft = 0;
	return (0);
}

void	reset_sector_indexes(t_editor_sector **head)
{
	t_editor_sector	*temp;
	int				idx;

	idx = 0;
	temp = *head;
	while (temp)
	{
		temp->idx_sector = idx;
		temp = temp->next;
		idx++;
	}
}

void	editor_free_sector_data(t_editor_sector **sector,
		t_entity_list **entity_head)
{
	t_editor_sector	*temp;

	temp = *sector;
	delete_entities_from_sector(entity_head, temp->idx_sector);
	editor_free_walls(&temp->walls, temp->nb_of_walls);
	if (temp->plot_line)
		free(temp->plot_line);
	free(temp);
}

void	editor_free_selected_sector(t_editor_sector **head,
		t_entity_list **entity_head, t_action *action)
{
	t_editor_sector	*temp;
	t_editor_sector	*prev;

	if (!*head)
		return ;
	temp = *head;
	if (temp != NULL && temp->idx_sector == action->selected_sector)
	{
		*head = temp->next;
		editor_free_sector_data(&temp, entity_head);
		reset_sector_indexes(head);
		return ;
	}
	while (temp != NULL && temp->idx_sector != action->selected_sector)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	editor_free_sector_data(&temp, entity_head);
	reset_sector_indexes(head);
}
