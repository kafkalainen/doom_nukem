/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:07:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/27 17:15:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static Uint32	get_half_way_point(t_point_data *left, t_point_data *right,
// 				t_xyz *left_xyz, t_xyz *right_xyz)
// {
// 	t_xy	min;
// 	t_xy	max;
// 	float	dist;
// 	float	angle;

// 	min.x = ft_fmin(left_xyz->x, right_xyz->x);
// 	max.x = ft_fmax(left_xyz->x, right_xyz->x);
// 	min.y = ft_fmin(left_xyz->z, right_xyz->z);
// 	max.y = ft_fmax(left_xyz->z, right_xyz->z);
// 	dist = vec2_eucl_dist(min, max);
// 	angle = vec2_ang(min, max);
// 	if (dist > 0.25f)
// 	{
// 		// dist = 0.5f * dist - 0.125f;
// 		// left->x = min.x + (dist * cosf(angle));
// 		// left->y = min.y + (dist * sinf(angle));
// 		// dist += 0.25f;
// 		// right->x = min.x + (dist * cosf(angle));
// 		// right->y = min.y + (dist * cosf(angle));
// 	}
// 	return (0);
// }

static Uint32	generate_a_button(t_wall *wall)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_wall;


	// get_half_way_point(&left, &right, &wall->top.p[1], &wall->top.p[2]);
	left.ceiling = wall->bottom.p[0].y + 2.0f;
	right.ceiling = left.ceiling;
	left.ground = wall->bottom.p[0].y;
	right.ground = left.ground;
	if (wall->light_switch.on_off)
		left.idx = -button_on;
	else
		left.idx = -button_off;
	left.light_switch = wall->light_switch.is_switch;
	left.on_off = wall->light_switch.on_off;
	left.power_station = 0;
	wall->light_switch.is_switch = 0;
	wall->light_switch.on_off = 0;
	new_wall = new_point(&left, &right);
	if (!new_wall)
		return (0);
	add_to_middle(&wall, new_wall);
	return (1);
}

// static Uint32	generate_a_power_station(t_wall *wall)
// {
// 	t_point_data	left;
// 	t_point_data	right;
// 	t_wall			*new_wall;

// 	left.x = portal->top.p[1].x;
// 	right.x = portal->top.p[2].x;
// 	left.y = portal->top.p[1].z;
// 	right.y = portal->top.p[2].z;
// 	left.ceiling = portal->top.p[1].y;
// 	right.ceiling = portal->top.p[2].y;
// 	left.ground = portal_behind->top.p[2].y;
// 	right.ground = portal_behind->top.p[1].y;
// 	portal_behind->top.p[2].y = portal->top.p[1].y;
// 	portal_behind->top.p[1].y = portal->top.p[2].y;
// 	portal_behind->bottom.p[1].y = portal->top.p[1].y;
// 	if (portal->next->top.idx < 0)
// 		left.idx = portal->next->top.idx;
// 	else
// 		left.idx = -2;
// 	new_wall = new_point(&left, &right);
// 	if (!new_wall)
// 		return (0);
// 	add_to_middle(&portal_behind, new_wall);
// 	return (1);
// }

void	calc_wall_objects(t_home *home)
{
	Uint32	i;
	Uint32	j;
	t_wall	*current_wall;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		current_wall = home->sectors[i]->walls;
		while (j < home->sectors[i]->nb_of_walls)
		{
			if (current_wall->light_switch.is_switch)
			{
				home->sectors[i]->nb_of_walls += generate_a_button(current_wall);
				current_wall = current_wall->next;
			}
			// if (current_wall->station.is_power_station)
			// 	home->sectors[current_wall->top.idx]->nb_of_walls
			// 		+= generate_a_power_station(current_wall);
			current_wall = current_wall->next;
			j++;
		}
		i++;
	}
}
