/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:51:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 15:12:09 by jnivala          ###   ########.fr       */
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

	temp = get_editor_sector_with_idx(&editor->sector_list,
			action->selected_sector);
	if (temp && mouse_data->i_mbright)
		return (editor_sector_remove_wallpoint(editor, temp));
	if (temp && mouse_data->i_mbleft)
	{
		if (add_point_to_list(editor, temp, action) == 3)
		{
			editor->temp_sector = NULL;
			editor->action.draw_depth = depth_zero;
			editor->action.create_sector = idle;
			editor->mouse_data.i_mbleft = 0;
			return (1);
		}
	}
	mouse_data->i_mbleft = 0;
	return (0);
}

void	reset_sector_indexes(t_editor_sector **head,
	t_entity_list **entity_head)
{
	t_editor_sector	*temp;
	int				idx;

	idx = 0;
	temp = *head;
	while (temp)
	{
		loop_for_portals_and_set_them_to_new_idx(temp, head, idx);
		loop_through_entities_and_reset_indexes(temp, entity_head, idx);
		temp->idx_sector = idx;
		temp = temp->next;
		idx++;
	}
	reset_elevators(head, entity_head);
}

void	editor_free_sector_data(t_editor_sector **sector,
	t_editor_sector **head, t_entity_list **entity_head)
{
	t_editor_sector	*temp;

	temp = *sector;
	delete_entities_from_sector(entity_head, temp->idx_sector);
	editor_free_walls(&temp->walls, temp->nb_of_walls);
	if (temp->plot_line)
		free(temp->plot_line);
	temp->plot_line = NULL;
	free(temp);
	temp = NULL;
	reset_sector_indexes(head, entity_head);
}

void	editor_free_selected_sector(t_editor_sector **head,
		t_entity_list **entity_head, t_action *action)
{
	t_editor_sector	*temp;
	t_editor_sector	*prev;

	if (!*head)
		return ;
	temp = *head;
	prev = NULL;
	if (temp != NULL && temp->idx_sector == action->selected_sector)
	{
		*head = temp->next;
		check_for_portals_and_set_defaults(temp, head);
		editor_free_sector_data(&temp, head, entity_head);
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
	check_for_portals_and_set_defaults(temp, head);
	editor_free_sector_data(&temp, head, entity_head);
}
