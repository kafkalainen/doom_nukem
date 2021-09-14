/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:51:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/14 17:55:44 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	handle_removal(t_editor_sector *sector_list, t_action *action)
{
	t_editor_walls *temp;

	temp = sector_list->walls;
	if (sector_list->nb_of_walls == 1)
		return ;
	while (temp && sector_list->nb_of_walls > action->selected_point)
	{
		remove_last_point(&temp, &sector_list->nb_of_walls, action->selected_point);
	}
	action->selected_point -= 1;
}

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

int		editor_new_sector_wallpoints(t_editor *editor,
		t_mouse_data *mouse_data, t_action *action)
{
	t_editor_sector	*temp;

	temp = editor->sector_list;
	while (temp != NULL && temp->idx_sector != action->selected_sector)
		temp = temp->next;
	if (action->delete)
	{
		handle_removal(temp, action);
		action->delete = 0;
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

int		get_sector_count(t_editor_sector **list)
{
	t_editor_sector	*temp;
	unsigned int	i;

	temp = *list;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	reset_sector_indexes(t_editor_sector **head)
{
	t_editor_sector	*temp;
	int				idx;
	int				nbr_of_sectors;

	nbr_of_sectors = get_sector_count(head);
	temp = *head;
	idx = 0;
	while (idx < nbr_of_sectors)
	{
		temp->idx_sector = idx;
		temp = temp->next;
		idx++;
	}
}

// void	delete_entities_from_sector(t_entity_list **entity_head, int sector_idx, t_action *action)
// {
// 	t_entity_list	*temp;
// 	t_entity_list	*prev;
// 	int				nbr_of_entities;
// 	int				i;
// 	int				nbr_to_delete;

// 	i = 0;
// 	nbr_to_delete = 0;
// 	nbr_of_entities = get_entity_count(entity_head);
// 	temp = *entity_head;
// 	while (i < nbr_of_entities && temp != NULL)
// 	{
// 		if (temp->sector_idx == sector_idx)
// 			nbr_to_delete++;
// 		i++;
// 		temp = temp->next;
// 	}
// }

void	editor_free_selected_sector(t_editor_sector **head, t_entity_list **entity_head, t_action *action)
{
	t_editor_sector	*temp;
	t_editor_sector	*prev;

	temp = *head;
	(void)entity_head;
	if (temp == NULL)
		return ;
	if (temp != NULL && temp->idx_sector == action->selected_sector)
	{
		*head = temp->next;
		// delete_entities_from_sector(entity_head, temp->idx_sector, action);
		editor_free_walls(&temp->walls, temp->nb_of_walls);
		if (temp->plot_line)
			free(temp->plot_line);
		free(temp);
		reset_sector_indexes(head);
		action->delete = 0;
		action->selected_sector = -1;
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
	// delete_entities_from_sector(entity_head, temp->idx_sector, action);
	editor_free_walls(&temp->walls, temp->nb_of_walls);
	if (temp->plot_line)
		free(temp->plot_line);
	free(temp);
	reset_sector_indexes(head);
	action->delete = 0;
	action->selected_sector = -1;
}
