/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:11:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/10 21:14:19 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		main_button_actions(t_action *action, int i)
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
	else if (i == button_create_sector)
	{
		if (action->create_sector == idle)
			action->create_sector = allocate;
	}
	else if (i == button_assign_end_sector)
		action->assign_end_sector = 1;
	else if (i == button_link_map  && action->nbr_of_maps > 0)
		action->link_maps = 1;
	else if (i == button_unlink_map)
		action->unlink_maps = 1;
	else if (i == button_plr_start)
		action->assign_player_start = 1;
	else if (i == button_create_elevator)
		action->create_elevator = 1;
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
	else if (i == button_create_light_src)
		action->create_light_source = 1;
	else if (i == button_input_active)
		action->input_active = 1;
	else if (i == button_add_wall_point)
		action->add_wall_point = 1;
}

void	entity_button_actions(t_action *action, int i)
{
	action->edit_entity = 1;
	if (i == button_change_entity_type)
		action->change_entity_type = 1;
	else if (i == button_toggle_entity_is_linked)
		action->toggle_entity_is_linked = 1;
	else if (i == button_toggle_is_revealed)
		action->toggle_is_revealed = 1;
	else if (i == button_toggle_is_static)
		action->toggle_is_static = 1;
	else if (i == button_toggle_state)
		action->toggle_state = 1;
}

void	wall_button_actions(t_action *action, int i)
{
	action->edit_wall = 1;
	if (i == button_change_wall_tex)
		action->change_wall_texture = 1;
	else if (i == button_convert_to_portal)
		action->convert_to_portal = 1;
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
	{
		action->create_light_button = 1;
		printf("add a light button\n");
	}

	else if (i == button_create_powerstation)
	{
		action->create_powerstation = 1;
		printf("add a powerstation\n");
	}

}

t_bool	check_bbox(t_xy start, t_xy end, t_xy click)
{
	if (start.x <= click.x && start.y >= click.y &&
		end.x >= click.x && end.y <= click.y)
		return (true);
	else
		return (false);
}

t_bool	check_bbox_ui(t_xy start, t_xy end, t_xy click)
{
	if (start.x <= click.x && start.y <= click.y &&
		end.x >= click.x && end.y >= click.y)
		return (true);
	else
		return (false);
}
