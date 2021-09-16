/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_reset_player_and_end.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:22:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 16:37:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_reset_player_and_end(t_editor *editor, t_action *action)
{
	if (action->selected_sector == editor->end_sector)
	{
		editor->end_sector = -1;
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
