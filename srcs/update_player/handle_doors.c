/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:18:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 11:25:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	lock_the_door(t_wall *dimensions, t_wall *door)
{

	door->top.p[0] = dimensions->top.p[0];
	door->top.p[1] = dimensions->top.p[1];
	door->top.p[2] = dimensions->top.p[2];
	door->bottom.p[0] = dimensions->bottom.p[0];
	door->bottom.p[1] = dimensions->bottom.p[1];
	door->bottom.p[2] = dimensions->bottom.p[2];
	door->top.uv[0] = dimensions->top.uv[0];
	door->top.uv[1] = dimensions->top.uv[1];
	door->top.uv[2] = dimensions->top.uv[2];
	door->bottom.uv[0] = dimensions->bottom.uv[0];
	door->bottom.uv[1] = dimensions->bottom.uv[1];
	door->bottom.uv[2] = dimensions->bottom.uv[2];
	door->top = translate_triangle(&door->top,
		vec3_mul(door->top.normal, -0.05f));
	door->bottom = translate_triangle(&door->bottom,
		vec3_mul(door->bottom.normal, -0.05f));
}

/*
**	v = h / t
**	h = vt
*/
static void	translate_door(t_wall *door, float speed, float time)
{
	t_xyz	translation_top;
	t_xyz	translation_bottom;
	float	denom;

	if (speed >= 0.0f)
		denom = time * 0.4f;
	else
		denom = -time * 0.4f;
	translation_top = (t_xyz){0.0f, speed * time, 0.0f, 1.0f};
	translation_bottom = (t_xyz){0.0f, speed * time, 0.0f, 1.0f};
	door->top.uv[1].v += denom;
	door->top.uv[2].v += denom;
	door->bottom.uv[1].v += denom;
	door->top.p[0] = translate_point(&door->top.p[0], translation_top);
	door->bottom.p[0] = translate_point(&door->bottom.p[0], translation_bottom);
	door->bottom.p[2] = translate_point(&door->bottom.p[2], translation_bottom);
}

static Uint32	handle_door_logic(t_wall *wall, Uint32 current_time,
			Uint32 delta_time)
{
	float	current_height;

	current_height = wall->next->top.p[2].y - wall->next->top.p[0].y;
	if (wall->open_until < current_time)
	{
		if (!wall->is_closed)
		{
			lock_the_door(wall, wall->next);
			wall->is_closed = 1;
		}
		return (1);
	}
	else
	{
		if (wall->next->height - current_height > 1.5f)
			wall->is_closed = 0;
		if (wall->open_until - 2500 > current_time)
			translate_door(wall->next, wall->height * 0.4f,
				delta_time * 0.001f);
		else
			translate_door(wall->next, -wall->height * 0.4f,
				delta_time * 0.001f);
	}
	return (0);
}

Uint32	update_doors(t_sector **sectors, Uint32 nb_of_sectors,
		Uint32 current_time, Uint32 delta_time)
{
	Uint32	i;
	Uint32	walls;
	t_wall	*wall;
	Uint32	volume;

	i = 0;
	volume = 0;
	while (i < nb_of_sectors)
	{
		walls = sectors[i]->nb_of_walls;
		wall = sectors[i]->walls;
		while (walls)
		{
			if (wall->is_door)
				volume += handle_door_logic(wall, current_time, delta_time);
			wall = wall->next;
			walls--;
		}
		i++;
	}
	return (volume);
}

int	open_door(t_sector **sectors, t_xyz look_loc,
	Uint32 current_time, Uint32 cur_sector)
{
	t_wall			*wall;
	t_wall			*portal_behind;

	wall = check_if_crossing(sectors[cur_sector], look_loc);
	if (wall && wall->is_door && wall->is_locked == unlocked)
	{
		portal_behind = get_portal_by_idx(cur_sector,
				sectors[wall->top.idx]);
		portal_behind->open_until = current_time + 5000;
		wall->open_until = current_time + 5000;
		return (1);
	}
	return (0);
}
