/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:25:29 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/11 09:46:09 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


void	check_ui_events(int x, int y, t_button ***blist, t_action *action)
{
	t_button	**list;
	int			i;
	t_xy		click_ui;

	i = 0;
	list = *blist;
	click_ui = vec2(x, y);
	while (i < NBR_BUTTONS)
	{
		if (list[i]->info.draw_depth == action->draw_depth)
		{
			if (check_bbox_ui(list[i]->ltop, list[i]->wh, click_ui))
			{
				if (list[i]->info.draw_depth == depth_zero)
					main_button_actions(action, i);
				else if (list[i]->info.draw_depth == sector)
					sector_button_actions(action, i);
				else if (list[i]->info.draw_depth == entity)
					entity_button_actions(action, i);
				else if (list[i]->info.draw_depth == wall)
					wall_button_actions(action, i);
				break ;
			}
		}
		i++;
	}
	if (i == NBR_BUTTONS)
		reset_actions(action);
}

int	clicked_inside_grid(int x, int y, int height, int width)
{
	if (x > 300 && x < width && y > 0 && y < height)
		return (TRUE);
	return (FALSE);
}

int	clicked_inside_ui(int x, int y, int height, int width)
{
	if (x > 0 && x < 300 && x < width && y > 0 && y < height)
		return (TRUE);
	return (FALSE);
}

int	check_saving_prerequisites(t_editor *editor)
{
	if (editor->mapname == NULL || !editor->action.player_start_assigned || !editor->end_sector)
		return (FALSE);
	if (!check_plr_start_and_end_sector_exists(&editor->sector_list, editor->plr, editor->end_sector))
		return (FALSE);
	printf("Saving map into file\n");
	return (TRUE);
}

void	save_editor_map(t_editor *editor, t_home *home)
{
	if (editor->mapname == NULL || editor->action.input_active || !editor->action.map_name_set)
		read_input_string(&editor->mapname, &editor->action);
	if (!editor->action.input_active || editor->action.map_name_set)
	{
		if (!editor->action.map_name_set && editor->mapname != NULL)
		{
			editor->mapname = (unsigned char *)ft_strjoin_freeable((char *)editor->mapname, ".DN", 1, 0);
			editor->mapname = (unsigned char *)ft_strjoin_freeable("./map_files/", (char *)editor->mapname, 0, 1);
			editor->action.map_name_set = 1;
		}
		if (check_saving_prerequisites(editor))
			create_map_file(home, editor);
		editor->action.save_file = 0;
	}
}
