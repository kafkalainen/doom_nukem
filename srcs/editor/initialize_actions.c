/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:02:20 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/20 15:45:05 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_menu_selections(t_action *action)
{
	action->grid = 1;
	action->selected_sector = -1;
	action->selected_entity = -1;
	action->selected_wall = -1;
	action->create_sector = idle;
	action->create_entity = idle;
	action->link_entity = 0;
	action->prev_entity = -1;
	action->edit_sector = idle;
	action->link_maps = 0;
	action->unlink_maps = 0;
	action->open_file = 0;
	action->save_file = 0;
	action->draw_depth = 0;
	action->delete = 0;
	action->edit_entity = 0;
}

static void	initialize_toggles(t_action *action)
{
	action->change_entity_type = 0;
	action->toggle_entity_is_linked = 0;
	action->toggle_is_revealed = 0;
	action->create_elevator = 0;
	action->create_light_button = 0;
	action->create_elev_button = 0;
	action->create_powerstation = 0;
	action->map_name_set = 0;
	action->player_start_assigned = 0;
	action->assign_end_sector = 0;
	action->assign_player_start = 0;
	action->unlink_entity = 0;
	action->edit_wall = 0;
	action->edit_floor_height = 0;
	action->edit_ceiling_height = 0;
	action->convert_to_portal = 0;
	action->change_wall_texture = 0;
	action->change_floor_texture = 0;
	action->change_ceiling_texture = 0;
	action->set_light_intensity = 0;
	action->create_light_source = 0;
	action->add_wall_point = 0;
	action->set_all_sector_ceiling_heights = 0;
	action->set_all_sector_floor_heights = 0;
	action->cycle_door = false;
}

static void	initialize_input(t_action *action)
{
	action->input_active = 0;
	action->keysym = -1;
}

void	initialize_actions(t_action *action)
{
	action->offsetf = vec2(0.0f, 0.0f);
	action->scalarf = 0.125f;
	action->write_sector_story = 0;
	action->prev_sector = -1;
	action->prev_wall = -1;
	initialize_menu_selections(action);
	initialize_toggles(action);
	initialize_input(action);
}
