/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:02:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 15:29:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_animation_on(Uint32 *start, Uint32 *end_time,
	Uint32 *current, Uint32 duration)
{
	if (!*start)
	{
		*start = 1;
		*end_time = *current + duration;
	}
}

static void	set_height(t_player *plr, char direction)
{
	if (direction == 'u')
	{
		plr->height += 0.1f;
		if (plr->height > 1.5f)
			plr->height = 1.5f;
		else
			plr->pos.y += 0.1f;
	}
	else if (direction == 'd')
	{
		plr->height -= 0.1f;
		if (plr->height <= 0.6f)
			plr->height = 0.6f;
		else
			plr->pos.y -= 0.1f;
	}
	else
		return ;
}

//static void	set_jump_sequence(t_player *plr, Uint32 *animation_end,
//	float *jump_range)
//{
//	if ((*animation_end - plr->time) > 450)
//	{
//		plr->pos.y -= 0.05f;
//		*jump_range -= 0.05f;
//	}
//	else
//	{
//		plr->pos.y += 0.2f;
//		*jump_range += 0.2f;
//	}
//}

void	crouch(t_player *plr)
{
	static Uint32	animation_start = 0;
	static Uint32	animation_end = 0;

	if (plr->input.crouch == 1)
	{
		set_animation_on(&animation_start, &animation_end, &plr->time, 100);
		if (plr->time <= animation_end)
			set_height(plr, 'd');
		else
			animation_start = 0;
	}
	else if (plr->input.crouch == 0)
	{
		set_animation_on(&animation_start, &animation_end, &plr->time, 100);
		if (plr->time <= animation_end)
			set_height(plr, 'u');
		else
			animation_start = 0;
	}
	else
		return ;
}

void	jump(t_player *plr, t_sector *sector)
{
	t_xyz	new_pos;

	new_pos = (t_xyz){plr->pos.x, plr->pos.y + 2.0f, plr->pos.z, plr->pos.w};
	if (plr->input.jump == 1
		&& !check_distance_to_ceiling(sector, &new_pos)
		&& check_distance_to_ground(sector, plr->height, plr->pos) <= 0)
	{
		plr->speed.y += 0.08f;
	}
	else
	{
		plr->input.jump = 0;
	}
}

int	jetpack(t_player *plr, t_home *home, Uint32 t)
{
	t_wall	*wall;
	float	dist;

	if (!plr->input.jetpack)
		return (FALSE);
	if (plr->fuel_points > 1)
	{
		plr->fuel_points -= t * 0.05f;
		plr->move_dir = vec3_unit_vector(plr->look_dir);
		plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->look_dir, t * 0.003f));
		if (check_distance_to_ceiling(home->sectors[plr->cur_sector],
				&plr->test_pos))
			return (FALSE);
		wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
				plr->width, plr->test_pos, plr->move_dir);
		if (!wall)
		{
			plr->pos = plr->test_pos;
			plr->steps += t * 0.005f;
			check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
			dist = check_distance_to_ground(home->sectors[plr->cur_sector],
					plr->height, plr->pos);
			if (dist < 0 && dist > -plr->height)
				plr->pos.y -= dist;
			return (TRUE);
		}
		return (FALSE);
	}
	else
	{
		plr->input.jetpack = 0;
	}
	return (FALSE);
}
