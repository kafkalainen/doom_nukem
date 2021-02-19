/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:08:50 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/19 10:31:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			player_move_forward(t_player *plr, t_home *home, float delta_time)
{
	play_footsteps(plr);
	//plr->pos = vec2_add(plr->pos, vec2_mul(plr->dir, 40 * delta_time));
	translate_world_view(home, vec2_mul(plr->dir, 40 * delta_time));
}

void			player_move_backwards(t_player *plr, t_home *home, float delta_time)
{
	play_footsteps(plr);
	//plr->pos = vec2_add(plr->pos, vec2_mul(plr->dir, 40 * delta_time));
	translate_world_view(home, vec2_mul(plr->dir, -40 * delta_time));
}

void			player_move_strafe(t_player *plr, t_home *home, float delta_time, char ad)
{
	t_xy	step;
		if (ad == 'd')
		{
			// plr->pos = vec2_add(plr->pos, vec2_mul(vec2_rot(
			//plr->dir, 90 * DEG_TO_RAD), 4 * delta_time));
			translate_world_view(home, vec2_mul(vec2_rot(
			plr->dir, FOV), 40 * delta_time));
			// step = vec2(1, 0);
			// translate_world_view(step, home);
		}
		else
		{
			// plr->pos = vec2_dec(plr->pos, vec2_mul(vec2_rot(
			// 	plr->dir, 90 * DEG_TO_RAD), 4 * delta_time));
			translate_world_view(home, vec2_mul(vec2_rot(
			plr->dir, FOV), -40 * delta_time));
			// step = vec2(-1, 0);
			// translate_world_view(step, home);
		}
	/*}*/
}

void				movement(t_player *plr, t_home *home)
{
	float		delta_time;
	clock_t		ctime;

	ctime = clock();
	delta_time = ((ctime - plr->time) / (float)CLOCKS_PER_SEC);
	if (delta_time < 0.0166667)
		return;
	plr->time = ctime;
	if (plr->input.down == 1)
		player_move_backwards(plr, home, delta_time);
	else if (plr->input.up == 1)
		player_move_forward(plr, home, delta_time);
	if (plr->input.right == 1)
		player_move_strafe(plr, home, delta_time, 'd');
	if (plr->input.left == 1)
		player_move_strafe(plr, home, delta_time, 'a');
}
