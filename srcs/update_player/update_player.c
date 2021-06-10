/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/10 08:13:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	ERRORZ
*/
// // static void	check_player_dir(t_player *plr, t_xy *dir)
// // {
// // 	if (plr->input.up == 1)
// // 	{
// // 		if (plr->input.left == 1)
// // 			*dir = vec2_rot(*dir, -45 * DEG_TO_RAD);
// // 		else if (plr->input.right == 1)
// // 			*dir = vec2_rot(*dir, 45 * DEG_TO_RAD);
// // 	}
// // 	if (plr->input.down == 1)
// // 	{
// // 		if (plr->input.left == 1)
// // 			*dir = vec2_rot(*dir, -135 * DEG_TO_RAD);
// // 		else if (plr->input.right == 1)
// // 			*dir = vec2_rot(*dir, 135 * DEG_TO_RAD);
// // 		else
// // 			*dir = vec2_rot(*dir, 180 * DEG_TO_RAD);
// // 	}
// // 	else if (plr->input.up == 0)
// // 	{
// // 		if (plr->input.left == 1)
// // 			*dir = vec2_rot(*dir, -90 * DEG_TO_RAD);
// // 		if (plr->input.right == 1)
// // 			*dir = vec2_rot(*dir, 90 * DEG_TO_RAD);
// // 	}
// // }

// // void	gravity_func(t_player *plr, int floor_height, float gravity)
// // {
// // 	floor_height = floor_height;
// // 	// plr->z = plr->z - gravity;
// // 	if (plr->acceleration > 0)
// // 	{
// // 		plr->acceleration = plr->acceleration - gravity;
// // 		plr->height += plr->acceleration;
// // 	}
// // 	if (plr->acceleration < 0)
// // 	{
// // 		plr->acceleration = 0;
// // 		plr->height = 0;
// // 	}
// // }

static void	movement(t_player *plr, t_home *home, Uint32 delta_time)
{
	(void)home;
	(void)delta_time;
	// t_xy	plr_dir;
	// gravity_func(plr, floor_height, (delta_time * 0.05));
	// if (plr->input.up == 1 || plr->input.down == 1
	// 	|| plr->input.left == 1 || plr->input.right == 1)
	// {
	// 	plr_dir = (t_xy){0, 1};
	// 	check_player_dir(plr, &plr_dir);
	// 	plr_dir = vec2_mul(plr_dir, delta_time * 0.05);
	//
	if (plr->input.debug_up == 1)
		plr->camera.y += 0.05f;
	if (plr->input.debug_down == 1)
		plr->camera.y -= 0.05f;
	if (plr->input.debug_left == 1)
		plr->camera.x -= 0.05f;
	if (plr->input.debug_right == 1)
		plr->camera.x += 0.05f;
	if (plr->input.up == 1)
	{
		plr->camera = vec3_add(plr->camera, vec3_mul(plr->look_dir, 0.05f));
		player_move(plr, home);
	}
	if (plr->input.down == 1)
	{
		plr->camera = vec3_dec(plr->camera, vec3_mul(plr->look_dir, 0.05f));
		player_move(plr, home);
	}
	if (plr->input.left == 1)
		plr->yaw -= 0.02f;
	if (plr->input.right == 1)
		plr->yaw += 0.02f;
	// if (player_move(plr, home, &plr_dir))
	//  	play_footsteps(plr);
}

void	update_player(t_player *plr, t_home *home, Uint32 delta_time)
{
	// if (plr->input.rot_left == 1)
	// 	transform_world_view(home, DEG_TO_RAD * 0.5);
	// if (plr->input.rot_right == 1)
	// 	transform_world_view(home, DEG_TO_RAD * -0.5);
	movement(plr, home, delta_time);
}
