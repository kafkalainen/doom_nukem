/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/28 16:02:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_player_dir(t_player *plr, t_xy *dir)
{
	if (plr->input.up == 1)
	{
		if (plr->input.left == 1)
			*dir = vec2_rot(*dir, -45 * DEG_TO_RAD);
		else if (plr->input.right == 1)
			*dir = vec2_rot(*dir, 45 * DEG_TO_RAD);
	}
	if (plr->input.down == 1)
	{
		if (plr->input.left == 1)
			*dir = vec2_rot(*dir, -135 * DEG_TO_RAD);
		else if (plr->input.right == 1)
			*dir = vec2_rot(*dir, 135 * DEG_TO_RAD);
		else
			*dir = vec2_rot(*dir, 180 * DEG_TO_RAD);
	}
	else if (plr->input.up == 0)
	{
		if (plr->input.left == 1)
			*dir = vec2_rot(*dir, -90 * DEG_TO_RAD);
		if (plr->input.right == 1)
			*dir = vec2_rot(*dir, 90 * DEG_TO_RAD);
	}
}

void	gravity_func(t_player *plr, int floor_height, float gravity)
{
	plr->z = plr->z - gravity;
	if (plr->z < floor_height)
		plr->z = floor_height;
	if(plr->acceleration > 0)
	{
		plr->acceleration = plr->acceleration - gravity;
		plr->height += plr->acceleration;
	}
	if(plr->acceleration < 0)
	{
		plr->acceleration = 0;
		plr->height = 0;
	}
}

static void	movement(t_player *plr, t_home *home, int floor_height)
{
	Uint32	current_time;
	Uint32	delta_time;
	t_xy	plr_dir;

	current_time = SDL_GetTicks();
	delta_time = current_time - plr->time;
	if (delta_time < 1)
		return ;
	plr->time = current_time;
	gravity_func(plr, floor_height, (delta_time * 0.05));
	if (plr->input.up == 1 || plr->input.down == 1
		|| plr->input.left == 1 || plr->input.right == 1)
	{
		plr_dir = (t_xy){PLR_DIR, PLR_DIR};
		check_player_dir(plr, &plr_dir);
		plr_dir = vec2_mul(plr_dir, delta_time * 0.05);
		if (player_move(plr, home, &plr_dir))
			play_footsteps(plr);
	}
}

void	update_player(t_player *plr, t_home *home, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		key_input(plr, e);
		mouse_handle(plr, home, e);
	}
	if (plr->input.rot_left == 1)
		transform_world_view(home, DEG_TO_RAD * 0.5);
	if (plr->input.rot_right == 1)
		transform_world_view(home, DEG_TO_RAD * -0.5);
	movement(plr, home, home->sectors[plr->current_sector]->ground);
}
