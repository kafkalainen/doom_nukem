/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector_special_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 08:59:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 10:19:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_sector_letter(t_editor_sector *temp, t_editor	*editor,
		char c, t_plx_modifier *mod)
{
	t_xy			screen_coord;

	screen_coord = world_to_screen(temp->centroid,
			editor->action.scalarf, editor->action.offsetf,
			&editor->buffer);
	screen_coord.x -= 2.5f * mod->size;
	screen_coord.y -= 3.5f * mod->size;
	ft_c_pxl(&editor->buffer, screen_coord, c, *mod);
}

void	draw_sector_special_info(t_editor *editor)
{
	t_editor_sector	*temp;
	t_plx_modifier	mod;

	temp = editor->sector_list;
	mod.size = 3;
	mod.colour = get_color(white);
	mod.len = 1;
	while (temp)
	{
		if (temp->idx_sector == editor->end_sector)
			draw_sector_letter(temp, editor, 'e', &mod);
		if (temp->idx_sector == editor->plr.sector)
			draw_sector_letter(temp, editor, 'p', &mod);
		if (temp->is_elevator == true)
			draw_sector_letter(temp, editor, 'l', &mod);
		temp = temp->next;
	}
}
