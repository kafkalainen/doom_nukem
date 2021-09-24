/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:31:07 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/24 10:02:08 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	editor_sector_remove_wallpoint(t_editor *editor, t_editor_sector *sector)
{
	if (sector->nb_of_walls > 1)
		editor_remove_last_wall(sector);
	else
	{
		editor->temp_sector = NULL;
		editor->action.draw_depth = depth_zero;
		editor->action.create_sector = idle;
		editor->mouse_data.i_mbright = 0;
		return (1);
	}
	editor->mouse_data.i_mbright = 0;
	return (0);
}

void	reset_portals_to_default_walls(t_editor_sector *sector, int sector_idx)
{
	t_editor_walls	*wall;
	int				i;

	if (!sector)
		return ;
	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type == sector_idx)
			wall->type = -wall0;
		wall = wall->next;
		i++;
	}
}

void	check_for_portals_and_set_defaults(t_editor_sector *sector,
	t_editor_sector **head)
{
	t_editor_walls	*wall;
	t_editor_sector	*temp;
	int				i;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type >= 0)
		{
			temp = get_editor_sector_with_idx(head, wall->type);
			if (temp)
				reset_portals_to_default_walls(temp, sector->idx_sector);
		}
		wall = wall->next;
		i++;
	}
}

void	loop_for_portals_and_set_them_to_new_idx(t_editor_sector *sector,
	t_editor_sector **head, int new_idx)
{
	t_editor_walls	*wall;
	t_editor_walls	*temp_wall;
	t_editor_sector	*temp;
	int				i;

	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (wall->type >= 0)
		{
			temp = get_editor_sector_with_idx(head, wall->type);
			if (temp)
			{
				temp_wall = get_editor_wall_with_type(&temp->walls,
						temp->nb_of_walls, sector->idx_sector);
				if (temp_wall)
					temp_wall->type = new_idx;
			}
		}
		i++;
		wall = wall->next;
	}
}

void	loop_through_entities_and_reset_indexes(t_editor_sector *sector,
	t_entity_list **head, int new_idx)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->sector_idx == sector->idx_sector)
			temp->sector_idx = new_idx;
		temp = temp->next;
	}
}
