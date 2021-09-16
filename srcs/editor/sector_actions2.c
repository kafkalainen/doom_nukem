/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_actions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:31:07 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/16 14:31:35 by rzukale          ###   ########.fr       */
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
