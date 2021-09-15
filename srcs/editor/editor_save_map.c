/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:49:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 18:49:35 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	check_saving_prerequisites(t_editor *editor)
{
	if (editor->mapname == NULL || !editor->action.player_start_assigned
		|| !editor->end_sector)
		return (FALSE);
	if (!check_plr_start_and_end_sector_exists(&editor->sector_list,
			editor->plr, editor->end_sector))
		return (FALSE);
	return (TRUE);
}

void	save_editor_map(t_editor *editor, t_home *home)
{
	if (editor->mapname == NULL || editor->action.input_active
		|| !editor->action.map_name_set)
		read_input_string(&editor->mapname, &editor->action);
	if (!editor->action.input_active || editor->action.map_name_set)
	{
		if (!editor->action.map_name_set && editor->mapname != NULL)
		{
			editor->mapname = (unsigned char *)ft_strjoin_freeable(
					(char *)editor->mapname, ".DN", 1, 0);
			editor->mapname = (unsigned char *)ft_strjoin_freeable(
					"./map_files/", (char *)editor->mapname, 0, 1);
			editor->action.map_name_set = 1;
		}
		if (check_saving_prerequisites(editor))
		{
			create_map_file(home, editor);
		}
		editor->action.save_file = 0;
	}
}
