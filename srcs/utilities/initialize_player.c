/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 11:10:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 09:42:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_player_movement_vectors(t_player *plr)
{
	plr->dir = vec2(0.0f, 1.0f);
	plr->cur_sector = 0;
	plr->pos = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	plr->look_dir = (t_xyz){0.0f, 0.0f, 1.0f, 1.0f};
	plr->up = (t_xyz){0.0f, 1.0f, 0.0f, 1.0f};
	plr->target = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	plr->pitch = 0.0f;
	plr->yaw = 0.0f;
	plr->roll = 0.0f;
	plr->height = 1.5f;
	plr->width = 0.25f;
	plr->speed = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
}

static void	initialize_player_game_states(t_player *plr)
{
	plr->power_points = 5.0f;
	plr->fuel_points = 100.0f;
	plr->active_inv = -1;
	plr->active_wep = 0;
	plr->inventory[0].in_use = 0;
	plr->inventory[1].in_use = 0;
	plr->inventory[2].in_use = 0;
	plr->inventory[3].in_use = 0;
	plr->steps = 0.0f;
	plr->plot_state = no_plot;
	plr->ending_played = false;
	plr->wep[0].ammo = 0;
	plr->wep[0].fire_rate = 1.0f;
	plr->wep[0].type = 0;
	plr->display_object = 0;
	plr->dead = 0;
	plr->reload = 0;
	plr->recharge = 0;
	plr->controls_enabled = 1;
	plr->take_damage = 0;
}

static void	initialize_input_values(t_input *input)
{
	input->down = 0;
	input->up = 0;
	input->right = 0;
	input->left = 0;
	input->rot_right = 0;
	input->rot_left = 0;
	input->wireframe = 0;
	input->minimap = 1;
	input->info = 1;
	input->mouse = 1;
	input->debug_up = 0;
	input->debug_down = 0;
	input->debug_right = 0;
	input->debug_left = 0;
	input->jetpack = 0;
	input->jump = 0;
	input->crouch = 0;
	input->use = 0;
	input->shoot = 0;
	input->music = false;
	input->skip = 0;
}

void	initialize_player(t_player *plr)
{
	if (!plr)
		return ;
	initialize_player_movement_vectors(plr);
	plr->time = SDL_GetTicks();
	plr->msg_time = 0;
	plr->total_msg_time = 0;
	plr->cutscene = 0;
	plr->drop_time = 0;
	initialize_player_game_states(plr);
	initialize_input_values(&plr->input);
}
