/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:18:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 19:27:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	free_buttons(t_editor *editor)
{
	int	i;

	i = -1;
	while (++i < NBR_BUTTONS)
	{
		free(editor->button_list[i]->info.text);
		editor->button_list[i]->info.text = NULL;
		free(editor->button_list[i]);
		editor->button_list[i] = NULL;
	}
	free(editor->button_list);
	editor->button_list = NULL;
}

static void	free_map_name_data(t_editor *editor)
{
	int	i;

	i = 0;
	while (i < editor->action.nbr_of_maps)
		free(editor->map_names[i++]);
	if (editor && editor->map_names)
		free(editor->map_names);
	if (editor && editor->mapname)
		free(editor->mapname);
	if (editor && editor->linked_mapname)
		free(editor->linked_mapname);
	if (editor && editor->int_string)
		free(editor->int_string);
}

void	free_editor_data(t_editor *editor)
{
	if (editor && editor->buffer.pxl_buffer)
		free(editor->buffer.pxl_buffer);
	free_buttons(editor);
	free_map_name_data(editor);
	editor->temp_entity = NULL;
	editor->temp_sector = NULL;
	editor->temp_wall = NULL;
	free_all_entities(&editor->entity_list);
	editor_free_all_sectors(&editor->sector_list);
}
