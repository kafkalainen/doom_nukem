/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_editor_values.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:01:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 11:44:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_editor_values(t_editor *editor)
{
	editor->buffer.width = 1200;
	editor->buffer.height = 900;
	editor->buffer.lightness = 1.0f;
	editor->cur_time = SDL_GetTicks();
	editor->notification = NULL;
	editor->sector_list = NULL;
	editor->entity_list = NULL;
	editor->linked_mapname = NULL;
	editor->mapname = NULL;
	editor->temp_entity = NULL;
	editor->temp_sector = NULL;
	editor->temp_wall = NULL;
	editor->map_names = NULL;
	editor->int_string = NULL;
	editor->end_sector.sector = -1;
	editor->end_sector.x = 0;
	editor->end_sector.z = 0;
	editor->plr.x = 0;
	editor->plr.z = 0;
	editor->plr.sector = -1;
}
