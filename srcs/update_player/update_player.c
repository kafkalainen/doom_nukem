/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 10:33:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_player_dir(t_player *plr)
{
	t_m4x4	matrix;

	if (plr->input.left == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(PI_BY_TWO);
	if (plr->input.right == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(-PI_BY_TWO);
	if (plr->input.up == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(0.7853982);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(-0.7853982);
		else
			matrix = rotation_matrix_y(0);
	}
	if (plr->input.down == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(2.356194);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(-2.356194);
		else
			matrix = rotation_matrix_y(PI);
	}
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
		if (player_move(plr, home, delta_time) && plr->drop_time <= 0)
			play_footsteps(&plr->audio);
	}
}

static void	plr_shoot_handle(t_home *home, t_player *plr, Uint32 t)
{
	t_ray	ray;

	if (plr->wep[plr->active_wep].fire_rate > 0)
		plr->wep[plr->active_wep].fire_rate -= t * 0.001;
	else
		plr->wep[plr->active_wep].fire_rate = 0;
	if (!plr->input.shoot)
		return ;
	if (plr->wep[plr->active_wep].ammo > 0
		&& plr->wep[plr->active_wep].fire_rate <= 0)
	{
		plr->wep[plr->active_wep].fire_rate = 1.0f;
		plr->hud.vm_ry = -20;
		ray.pos = plr->pos;
		ray.dir = plr->look_dir;
		ray.side = PLAYER;
		ray.start_sector = plr->cur_sector;
		shooting_handle(home, &ray);
		plr->wep[plr->active_wep].ammo--;
		play_sound(plr->audio.plasma_gun, 30);
	}
	else if (plr->wep[plr->active_wep].ammo == 0)
		play_sound(plr->audio.plasma_gun_no_ammo, 30);
}

static void	update_player_values(t_player *plr, Uint32 delta_time)
{
	if (plr->input.rot_left == 1)
		plr->yaw -= 0.02f;
	if (plr->input.rot_right == 1)
		plr->yaw += 0.02f;
	if (plr->hud.vm_rx != 0)
		plr->hud.vm_rx *= 0.908f;
	if (plr->hud.vm_ry != 0)
		plr->hud.vm_ry *= 0.908f;
	if (plr->fuel_points < 100)
		plr->fuel_points = fmin(plr->fuel_points + 0.004f * delta_time, 100.0f);
}

void	update_player(t_player *plr, t_home *home, Uint32 delta_time)
{
	update_player_values(plr, delta_time);
	crouch(plr, home->sectors[plr->cur_sector]);
	plr_shoot_handle(home, plr, delta_time);
	if (!plr->input.jetpack)
		jump(plr, home->sectors[plr->cur_sector]);
	if (!plr->input.jetpack)
		plr->pos.y += plr->speed.y * delta_time * 0.001f;
	if (plr->input.jetpack)
		jetpack(plr, home, delta_time);
	gravity(home, plr, delta_time);
	if (!plr->input.jetpack)
		movement(plr, home, delta_time);
	unstuck(plr, home);
	player_use(plr, home);
	player_look(home, plr);
	reload_weapon(plr, delta_time);
	recharge_suit(plr, delta_time);
	if (plr->cur_sector != home->end_sector)
		evolve_story(plr, home->sectors[plr->cur_sector],
			home->sectors[plr->msg_sector], delta_time);
	if (plr->take_damage)
		update_damage_tick(delta_time, &plr->take_damage);
	if (plr->dead > 0)
		death_animation(home, plr, delta_time);
	end_level(home, plr);
}
