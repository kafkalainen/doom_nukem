/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:08:50 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/23 12:31:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int				check_collision(t_sector *sector, t_player *plr, t_home *home)
{
	t_ray			ray;
	t_intersection	isect;
	t_xy			point;
	t_point			*p0;
	int				i;

	i = 0;
	p0 = &sector->points[0];
	ray.pos = plr->pos;
	ray.dir = plr->move_dir;
	while (i < sector->nb_of_walls)
	{
		calc_intersection_raw(p0, &ray, &isect);
		point = line_intersection_raw(&isect);
		if (point.x >= 0 || point.y >= 0)
		{
			if (get_distance(vec2(0, 0), point) < 2 && (p0->idx >= 0))
			{
				plr->current_sector = p0->idx;
				translate_world_view(home, vec2_mul(plr->move_dir, 2));
				return (0);
			}
			else if (get_distance(vec2(0, 0), point) < 5 && (p0->idx < 0))
				return ((int)(vec2_ang(p0->x0, p0->next->x0) * RAD_TO_DEG));
		}
		p0 = p0->next;
		i++;
	}
	return (0);
}

static t_xy		check_player_dir(t_player *plr)
{
	float		def;

	def = 0.785398163;
	if (plr->input.up == 1)
		if (plr->input.left == 1)
			return (vec2_rot(vec2(def, def), -45 * DEG_TO_RAD));
		else if (plr->input.right == 1)
			return (vec2_rot(vec2(def, def), 45 * DEG_TO_RAD));
		else
			return (vec2(def, def));
	if (plr->input.down == 1)
		if (plr->input.left == 1)
			return (vec2_rot(vec2(def, def), -135 * DEG_TO_RAD));
		else if (plr->input.right == 1)
			return (vec2_rot(vec2(def, def), 135 * DEG_TO_RAD));
		else
			return (vec2_rot(vec2(def, def), 180 * DEG_TO_RAD));
	if (plr->input.left == 1)
		return (vec2_rot(vec2(def, def), -90 * DEG_TO_RAD));
	if (plr->input.right == 1)
		return (vec2_rot(vec2(def, def), 90 * DEG_TO_RAD));
}

void			player_move(t_player *plr, t_home *home, float delta_time)
{
	int		collision;
	t_xy	col_dir;

	collision = check_collision(home->sectors[plr->current_sector], plr, home);
	col_dir = vec2(1, 1);
	col_dir = vec2_rot(col_dir, collision * DEG_TO_RAD);
	plr->move_dir = check_player_dir(plr);
	play_footsteps(plr);
	if (!collision)
		translate_world_view(home, vec2_mul(plr->move_dir, 40 * delta_time));
	else
	{
		printf("col dir x: %f, col dir y: %f\n", col_dir.x, col_dir.y);
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
	if (plr->input.up == 1 || plr->input.down == 1
		|| plr->input.left == 1 || plr->input.right == 1)
		player_move(plr, home, delta_time);
	if (plr->input.z == 1)
		plr->z += 0.1;
	if (plr->input.x == 1)
		plr->z -= 0.1;
}
