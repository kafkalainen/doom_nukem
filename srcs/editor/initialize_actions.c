/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:02:20 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 08:15:27 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_menu_selections(t_action *action)
{
	action->grid = true;
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
	action->save_file = false;
	action->draw_depth = 0;
	action->delete = false;
	action->edit_entity = 0;
}

static void	initialize_toggles_two(t_action *action)
{
	action->set_all_sector_floor_heights = false;
	action->set_gravity = false;
	action->cycle_portal = false;
	action->add_poster = false;
}

static void	initialize_toggles(t_action *action)
{
	action->toggle_entity_is_linked = false;
	action->toggle_is_revealed = false;
	action->create_elevator = false;
	action->create_light_button = false;
	action->create_elev_button = false;
	action->create_powerstation = false;
	action->map_name_set = false;
	action->player_start_assigned = false;
	action->assign_end_sector = idle;
	action->assign_player_start = idle;
	action->unlink_entity = 0;
	action->edit_wall = false;
	action->edit_floor_height = false;
	action->edit_ceiling_height = false;
	action->convert_to_portal = idle;
	action->change_wall_texture = false;
	action->change_floor_texture = false;
	action->change_ceiling_texture = false;
	action->set_light_intensity = false;
	action->create_light_source = false;
	action->set_all_sector_ceiling_heights = false;
	initialize_toggles_two(action);
}

static void	initialize_input(t_action *action)
{
	action->input_active = false;
	action->keysym = -1;
}

void	initialize_actions(t_action *action, t_buffer *buffer)
{
	t_screen_xy	pos;

	pos.x = 0;
	pos.y = 0;
	action->offsetf = vec2(0.0f, 0.0f);
	action->scalarf = 0.125f;
	SDL_GetMouseState(&pos.x, &pos.y);
	action->mouse_pos = get_ndc(buffer, pos);
	action->world_pos = ndc_to_world(action->mouse_pos, action->offsetf,
			action->scalarf);
	action->write_sector_story = false;
	action->prev_sector = -1;
	action->prev_wall = -1;
	action->change_entity_type = false;
	initialize_menu_selections(action);
	initialize_toggles(action);
	initialize_input(action);
}
