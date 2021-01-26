/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:08:50 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/26 13:51:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			player_move_forward(t_player *plr, float delta_time)
{
	t_xy check_pos;

	check_pos = plr->pos;
	check_pos = vec2_add(check_pos, vec2_mul(plr->dir, 8 * delta_time));
	play_footsteps(plr);
	//if (valid_location(check_pos, map))
		plr->pos = vec2_add(plr->pos, vec2_mul(plr->dir, 40 * delta_time));
}

void			player_move_backwards(t_player *plr, float delta_time)
{
	t_xy check_pos;

	check_pos = plr->pos;
	check_pos = vec2_dec(check_pos, vec2_mul(plr->dir, 8 * delta_time));
	//if (valid_location(check_pos, map))
		plr->pos = vec2_dec(plr->pos, vec2_mul(plr->dir, 40 * delta_time));
}

void			player_move_strafe(t_player *plr, float delta_time, char ad)
{
	t_xy check_pos;

	check_pos = plr->pos;
	check_pos = (ad == 'd') ? vec2_add(plr->pos, vec2_mul(vec2_rot(
				plr->dir, 90 * DEG_TO_RAD), 8 * delta_time))
				: vec2_dec(plr->pos, vec2_mul(vec2_rot(
				plr->dir, 90 * DEG_TO_RAD), 8 * delta_time));
	//if (valid_location(vec2_mul(check_pos, 1.0), map))
	//{
		if (ad == 'd')
			plr->pos = vec2_add(plr->pos, vec2_mul(vec2_rot(
				plr->dir, 90 * DEG_TO_RAD), 4 * delta_time));
		else
			plr->pos = vec2_dec(plr->pos, vec2_mul(vec2_rot(
				plr->dir, 90 * DEG_TO_RAD), 4 * delta_time));
	//}
}

void				movement(t_player *plr)
{
	float		delta_time;
	clock_t		ctime;

	ctime = clock();
	delta_time = ((ctime - plr->time) / (float)CLOCKS_PER_SEC);
	if (delta_time < 0.0166667)
		return;
	plr->time = ctime;
	if (plr->input.down == 1)
		player_move_backwards(plr, delta_time);
	else if (plr->input.up == 1)
		player_move_forward(plr, delta_time);
	if (plr->input.right == 1)
		player_move_strafe(plr, delta_time, 'd');
	if (plr->input.left == 1)
		player_move_strafe(plr, delta_time, 'a');
}
