/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/28 16:35:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_player_dir(t_player *plr)
{
	t_m4x4	matrix;

	if (plr->input.up == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(-0.7853982);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(0.7853982);
		else
			matrix = rotation_matrix_y(0);
	}
	if (plr->input.down == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(-2.356194);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(2.356194);
		else
			matrix = rotation_matrix_y(PI);
	}
	if (plr->input.left == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(-PI_BY_TWO);
	if (plr->input.right == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(PI_BY_TWO);
	plr->move_dir = multi_vec_matrix(&plr->look_dir, &matrix);
}

static void	movement(t_player *plr, t_home *home, Uint32 delta_time)
{
	if (plr->input.debug_up == 1)
		plr->pos.y += 0.05f;
	if (plr->input.debug_down == 1)
		plr->pos.y -= 0.05f;
	if (plr->input.debug_left == 1)
		plr->pos.x -= 0.05f;
	if (plr->input.debug_right == 1)
		plr->pos.x += 0.05f;
	if (plr->input.up == 1 || plr->input.down == 1
		|| plr->input.left == 1 || plr->input.right == 1)
	{
		check_player_dir(plr);
		player_move(plr, home, delta_time);
		// if (player_move(plr, home, delta_time))
		// 	play_footsteps(&plr->audio);
	}
}

void	update_player(t_player *plr, t_home *home, Uint32 delta_time)
{
	if (plr->input.rot_left == 1)
		plr->yaw -= 0.02f;
	if (plr->input.rot_right == 1)
		plr->yaw += 0.02f;
	if (plr->hud.vm_rx != 0)
		plr->hud.vm_rx *= 0.908f;
	if (plr->hud.vm_ry != 0)
		plr->hud.vm_ry *= 0.908f;
	crouch(plr);
	if (!plr->input.jetpack)
		jump(plr, home->sectors[plr->cur_sector]);
	if (plr->fuel_points < 100)
		plr->fuel_points = fmin(plr->fuel_points + 0.004f * delta_time, 100.0f);
	if (!plr->input.jetpack)
		plr->pos.y += plr->speed.y * delta_time * 0.1f;
	jetpack(plr, home, delta_time);
	gravity(home->sectors[plr->cur_sector], plr, delta_time);
	if (!plr->input.jetpack)
		movement(plr, home, delta_time);
	player_use(plr, home, delta_time);
	evolve_story(plr, home->sectors[plr->cur_sector],
		home->sectors[plr->msg_sector]);
	end_level(home, plr);
}
