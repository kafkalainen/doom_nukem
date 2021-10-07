/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:18:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 20:27:26 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	lock_the_door(t_wall *dimensions, t_wall *door)
{
	door->top.p[0] = dimensions->top.p[0];
	door->top.p[1] = dimensions->top.p[1];
	door->top.p[2] = dimensions->top.p[2];
	door->bot.p[0] = dimensions->bot.p[0];
	door->bot.p[1] = dimensions->bot.p[1];
	door->bot.p[2] = dimensions->bot.p[2];
	door->top.uv[0] = dimensions->top.uv[0];
	door->top.uv[1] = dimensions->top.uv[1];
	door->top.uv[2] = dimensions->top.uv[2];
	door->bot.uv[0] = dimensions->bot.uv[0];
	door->bot.uv[1] = dimensions->bot.uv[1];
	door->bot.uv[2] = dimensions->bot.uv[2];
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
	door->bot.uv[1].v += denom;
	door->top.p[0] = translate_point(&door->top.p[0], translation_top);
	door->bot.p[0] = translate_point(&door->bot.p[0], translation_bottom);
	door->bot.p[2] = translate_point(&door->bot.p[2], translation_bottom);
}

static void	handle_door_logic(t_wall *wall, Uint32 current_time,
			Uint32 delta_time)
{
	float	current_height;

	current_height = wall->next->top.p[2].y - wall->next->top.p[0].y;
	if (wall->open_until < current_time)
	{
		if (!wall->is_closed)
		{
			lock_the_door(wall, wall->next);
			wall->is_closed = true;
		}
		return ;
	}
	else
	{
		if (wall->next->height - current_height > 1.5f)
			wall->is_closed = false;
		if (wall->open_until - 2500 > current_time)
			translate_door(wall->next, wall->height * 0.4f,
				delta_time * 0.001f);
		else
			translate_door(wall->next, -wall->height * 0.4f,
				delta_time * 0.001f);
	}
}

void	update_doors(t_sector **sectors, Uint32 nb_of_sectors,
		Uint32 current_time, Uint32 delta_time)
{
	Uint32	i;
	Uint32	walls;
	t_wall	*wall;

	i = 0;
	while (i < nb_of_sectors)
	{
		walls = sectors[i]->nb_of_walls;
		wall = sectors[i]->walls;
		while (walls)
		{
			if (wall->is_door)
				handle_door_logic(wall, current_time, delta_time);
			wall = wall->next;
			walls--;
		}
		i++;
	}
}

t_bool	open_door(t_sector **sectors, t_player *plr, int active_item)
{
	t_wall			*wall;
	t_wall			*portal_behind;

	wall = check_if_crossing(sectors[plr->cur_sector],
			plr->pos, plr->look_dir);
	if (wall && wall->is_door && wall->open_until < plr->time)
	{
		if (check_for_matching_key(wall, plr, active_item))
		{
			portal_behind = get_portal_by_idx(plr->cur_sector,
					sectors[wall->top.type]);
			check_for_matching_key(portal_behind, plr, active_item);
			portal_behind->open_until = plr->time + 5000;
			wall->open_until = plr->time + 5000;
			play_sound(plr->audio.door, 2);
			return (true);
		}
		play_sound(plr->audio.error, 20);
	}
	return (false);
}
