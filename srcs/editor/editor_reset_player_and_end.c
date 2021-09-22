/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_reset_player_and_end.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:51:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 09:51:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_reset_player_and_end(t_editor *editor, t_action *action)
{
	if (action->selected_sector == editor->end_sector.sector)
	{
		editor->end_sector.sector = -1;
		editor->end_sector.x = 0;
		editor->end_sector.z = 0;
	}
	if (action->player_start_assigned
		&& action->selected_sector == editor->plr.sector)
	{
		editor->plr.x = 0;
		editor->plr.z = 0;
		editor->plr.sector = -1;
		action->player_start_assigned = 0;
	}
}

void	check_pos_coordinates_to_sectors(t_plr_pos *pos, t_editor_sector **head)
{
	t_editor_sector	*temp;

	temp = *head;
	while (temp)
	{
		if (check_bbox(temp->bbox.start, temp->bbox.end,
				vec2((float)pos->x, (float)pos->z)))
		{
			pos->sector = temp->idx_sector;
			break ;
		}
		temp = temp->next;
	}
}

void	verify_plr_start_end_sector_coordinates(t_plr_pos *plr,
	t_editor_sector **head, t_plr_pos *end)
{
	if (plr->sector >= 0)
		check_pos_coordinates_to_sectors(plr, head);
	if (end->sector >= 0)
		check_pos_coordinates_to_sectors(end, head);
}
