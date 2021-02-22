/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:08:50 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/19 14:37:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int				check_collision(t_sector *sector, float delta_time, t_player *plr)
{
	t_ray			ray;
	t_intersection	isect;
	t_xy			point;
	t_point			*p0;
	int				i;

	i = 0;
	ray.dir = vec2(0.785398163, 0.785398163);
	ray.pos = vec2(-1, -1);
	t_point *start = &sector->points[0];
	p0 = start;
	while (i < sector->nb_of_walls)
	{
		calc_intersection(p0, start, &ray, &isect);
		point = line_intersection(&isect);
		if (point.x != -1 && point.y != -1)
		{
			if (get_distance(vec2(0, 0), point) < 5 && (p0->idx < 0))
				return (1);
			else if (get_distance(vec2(0, 0), point) < 3 && (p0->idx >= 0))
			{
				plr->current_sector = p0->idx;
				return (0);
			}
		}
		p0 = p0->next;
		i++;
	}
	return (0);
}

void			player_move_forward(t_player *plr, t_home *home, float delta_time)
{
	play_footsteps(plr);
	if (!check_collision(home->sectors[plr->current_sector], delta_time, plr))
		translate_world_view(home, vec2_mul(plr->dir, 40 * delta_time));
}

void			player_move_backwards(t_player *plr, t_home *home, float delta_time)
{
	play_footsteps(plr);
	translate_world_view(home, vec2_mul(plr->dir, -40 * delta_time));
}

void			player_move_strafe(t_player *plr, t_home *home, float delta_time, char ad)
{
	t_xy	step;
	if (ad == 'd')
	{
		translate_world_view(home, vec2_mul(vec2_rot(
		plr->dir, FOV), 40 * delta_time));
	}
	else
	{
		translate_world_view(home, vec2_mul(vec2_rot(
		plr->dir, FOV), -40 * delta_time));
	}
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
	if (plr->input.z == 1)
		plr->z += 0.1;
	if (plr->input.x == 1)
		plr->z -= 0.1;
}
