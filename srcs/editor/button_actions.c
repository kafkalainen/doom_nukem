/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:11:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 17:14:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	main_button_actions(t_action *action, int i)
{
	if (i == button_save)
	{
		action->save_file = 1;
		if (!action->map_name_set)
			action->input_active = 1;
	}
	else if (i == button_open && action->nbr_of_maps > 0)
		action->open_file = 1;
	else if (i == button_activate_grid)
	{
		if (action->grid)
			action->grid = 0;
		else
			action->grid = 1;
	}
	else if (i == button_assign_end_sector)
		action->assign_end_sector = 1;
	else if (i == button_link_map && action->nbr_of_maps > 0)
		action->link_maps = 1;
	else if (i == button_unlink_map)
		action->unlink_maps = 1;
	else if (i == button_plr_start)
		action->assign_player_start = 1;
}

static void	sector_button_actions_two(t_action *action, int i)
{
	if (i == button_create_portal)
		action->convert_to_portal = 1;
	else if (i == button_set_all_ceiling_heights)
	{
		action->set_all_sector_ceiling_heights = 1;
		action->input_active = 1;
	}
	else if (i == button_set_all_floor_heights)
	{
		action->set_all_sector_floor_heights = 1;
		action->input_active = 1;
	}
}

void	sector_button_actions(t_action *action, int i)
{
	action->edit_sector = 1;
	if (i == button_change_floor_tex)
		action->change_floor_texture = 1;
	else if (i == button_change_ceil_tex)
		action->change_ceiling_texture = 1;
	else if (i == button_set_light_intensity)
	{
		action->input_active = 1;
		action->set_light_intensity = 1;
	}
	else if (i == button_convert_to_elevator)
		action->create_elevator = 1;
	else if (i == button_create_light_src)
		action->create_light_source = 1;
	else if (i == button_input_active)
	{
		action->write_sector_story = 1;
		action->input_active = 1;
	}
	sector_button_actions_two(action, i);
}

void	entity_button_actions(t_action *action, int i)
{
	action->edit_entity = 1;
	if (i == button_change_entity_type)
		action->change_entity_type = 1;
	else if (i == button_toggle_entity_is_linked)
		action->toggle_entity_is_linked = 1;
	else if (i == button_toggle_state)
		action->toggle_state = 1;
}

void	wall_button_actions(t_action *action, int i)
{
	action->edit_wall = 1;
	if (i == button_change_wall_tex)
		action->change_wall_texture = 1;
	else if (i == button_set_ceiling_height)
	{
		action->edit_ceiling_height = 1;
		action->input_active = 1;
	}
	else if (i == button_set_floor_height)
	{
		action->edit_floor_height = 1;
		action->input_active = 1;
	}
	else if (i == button_create_light_button)
		action->create_light_button = 1;
	else if (i == button_create_powerstation)
		action->create_powerstation = 1;
	else if (i == button_create_elevator_button)
		action->create_elev_button = 1;
	if (i == button_change_to_door)
		action->cycle_door = true;
}
