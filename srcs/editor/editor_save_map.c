/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:49:15 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/16 18:11:08 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_saving_prerequisites(t_editor *editor)
{
	if (!editor->mapname)
	{
		add_notification(editor, "Cannot save. Map name missing.", 3000);
		return (false);
	}
	if (!editor->action.player_start_assigned)
	{
		add_notification(editor, "Cannot save. Player start missing.", 3000);
		return (false);
	}
	if (editor->end_sector.sector == -1)
	{
		add_notification(editor, "Cannot save. Level end missing.", 3000);
		return (false);
	}
	return (true);
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
			editor->mapname = (t_uchar *)ft_strjoin_freeable(
					(char *)editor->mapname, ".DN", 1, 0);
			editor->mapname = (t_uchar *)ft_strjoin_freeable("./map_files/",
					(char *)editor->mapname, 0, 1);
			editor->action.map_name_set = 1;
		}
		if (check_saving_prerequisites(editor))
		{
			if(create_map_file(home, editor) == 1)
				add_notification(editor, "Map saved successfully\n", 3000);
			else
				add_notification(editor, "Error: Map saving failed\n", 3000);
		}
		editor->action.save_file = 0;
	}
}
