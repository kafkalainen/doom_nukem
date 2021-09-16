/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:31:07 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/16 15:13:41 by rzukale          ###   ########.fr       */
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
