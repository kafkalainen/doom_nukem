/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:27:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 13:59:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	draw_button_logic(t_editor *editor, int i)
{
	if (i == button_set_light_intensity)
	{
		if (editor->action.selected_sector >= 0
			&& !calc_linked_entities(&editor->entity_list,
				editor->action.selected_sector + 2, lamp))
			return (false);
	}
	return (true);
}

void	draw_button(t_editor *editor, t_button *button, int i)
{
	if (!draw_button_logic(editor, i))
		return ;
	button->mod.colour = get_color_from_action_data(i,
			&editor->action, editor->end_sector.sector);
	draw_box(button->box, &editor->buffer, get_color(0xAAAAAA));
	ft_str_pxl(&editor->buffer, button->text_loc,
		button->info.text, button->mod);
}
