/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:27:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/17 16:41:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_to_inactive(t_editor *editor, t_button *button, int type)
{
	if (editor->temp_sector
			&& calc_entities_in_sector_with_type(&editor->entity_list,
			editor->temp_sector->idx_sector, type))
		button->is_active = false;
	else
		button->is_active = true;
}

static void	draw_button_logic(t_editor *editor, t_button *button, int i)
{
	if (i == button_set_light_intensity)
	{
		if (editor->temp_sector
			&& !calc_entities_in_sector_with_type(&editor->entity_list,
				editor->temp_sector->idx_sector, lamp))
			button->is_active = false;
		else
			button->is_active = true;
	}
	if (i == button_create_light_src)
		set_to_inactive(editor, button, lamp);
	if (i == button_create_elevator_button)
		set_to_inactive(editor, button, lift_button);
	if (i == button_create_light_button)
		set_to_inactive(editor, button, light_button);
	if (i == button_change_to_door)
	{
		if (editor->temp_wall && editor->temp_wall->type >= 0)
			button->is_active = true;
		else
			button->is_active = false;
	}
}

void	draw_button(t_editor *editor, t_button *button, int i)
{
	draw_button_logic(editor, button, i);
	if (button->is_active)
		button->mod.colour = get_color_from_action_data(i,
				&editor->action, editor->end_sector.sector);
	else
		button->mod.colour = get_color(gray);
	draw_box(button->box, &editor->buffer, get_color(gray));
	ft_str_pxl(&editor->buffer, button->text_loc,
		button->info.text, button->mod);
}
