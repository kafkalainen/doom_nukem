/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:02:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 14:46:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_animation_on(Uint32 *start, Uint32 *end_time, Uint32 duration)
{
	if (!*start)
	{
		*start = 1;
		*end_time = duration;
	}
}

static void	set_height(t_player *plr, Uint32 t, char direction)
{
	if (direction == 'u')
	{
		plr->height += 0.005f * t;
		if (plr->height > 1.5f)
			plr->height = 1.5f;
		else
			plr->pos.y += 0.005f * t;
	}
	else if (direction == 'd')
	{
		plr->height -= 0.005f * t;
		if (plr->height <= 0.6f)
			plr->height = 0.6f;
		else
			plr->pos.y -= 0.005f * t;
	}
	else
		return ;
}

void	crouch(t_player *plr, t_sector *sector, Uint32 delta_time)
{
	static Uint32	animation_start = 0;
	static Uint32	animation_end = 0;

	if (plr->input.crouch == 1)
	{
		set_animation_on(&animation_start, &animation_end, 100);
		animation_start += delta_time;
		if (animation_start <= animation_end)
			set_height(plr, delta_time, 'd');
		else
			animation_start = 0;
	}
	else if (plr->input.crouch == 0
		&& !check_distance_to_ceiling(sector, &plr->pos))
	{
		set_animation_on(&animation_start, &animation_end, 100);
		animation_start += delta_time;
		if (animation_start <= animation_end)
			set_height(plr, delta_time, 'u');
		else
			animation_start = 0;
	}
	else
		return ;
}

void	jump(t_player *plr, t_sector *sector)
{
	float	dist;

	dist = 0.0f;
	check_distance_to_ground(sector, plr->height, plr->pos, &dist);
	if (plr->input.jump && dist <= 0.0f
		&& !check_distance_to_ceiling(sector, &plr->pos))
		plr->speed.y += 4.0f;
	if (check_distance_to_ceiling(sector, &plr->pos))
		plr->speed.y -= 4.0f;
	plr->input.jump = 0;
}

t_bool	jetpack(t_player *plr, t_home *home, Uint32 t)
{
	t_wall	*wall;

	if (plr->fuel_points > 1)
	{
		plr->fuel_points -= t * 0.05f;
		plr->move_dir = vec3_unit_vector(plr->look_dir);
		plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->look_dir, t * 0.004f));
		if (check_distance_to_ceiling(home->sectors[plr->cur_sector],
				&plr->test_pos))
			return (false);
		plr->move_dir = vec3_unit_vector(vec3(plr->look_dir.x,
					0.0f, plr->look_dir.z));
		wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
				plr->width, plr->test_pos, plr->move_dir);
		if (!wall)
		{
			plr->pos = plr->test_pos;
			check_if_moved_through_portal(&plr->cur_sector, plr->pos,
				plr->height, home);
			return (true);
		}
		plr->look_dir = wall->top.normal;
	}
	plr->input.jetpack = 0;
	return (false);
}
