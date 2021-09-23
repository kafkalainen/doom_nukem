/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_extra_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:05:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 10:12:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void	debug_original_walls(t_wall *portal, t_wall *portal_behind)
// {
// 	printf("LOWER WALL\n");
// 	printf("==================================\n");
// 	printf("ORIGINAL PORTAL\n");
// 	printf("left.x %f left.z %f left.ground %f left.ceil %f\n",
// 		portal->top.p[1].x, portal->top.p[1].z,
// 		portal->bottom.p[0].y, portal->top.p[1].y);
// 	printf("right.x %f right.z %f right.ground %f right.ceil %f\n",
// 		portal->top.p[2].x, portal->top.p[2].z,
// 		portal->bottom.p[2].y, portal->top.p[2].y);
// 	printf("ORIGINAL PORTAL BEHIND\n");
// 	printf("left.x %f left.z %f left.ground %f left.ceil %f\n",
// 		portal_behind->top.p[1].x, portal_behind->top.p[1].z,
// 		portal_behind->bottom.p[0].y, portal_behind->top.p[1].y);
// 	printf("right.x %f right.z %f right.ground %f right.ceil %f\n",
// 		portal_behind->top.p[2].x, portal_behind->top.p[2].z,
// 		portal_behind->bottom.p[2].y, portal_behind->top.p[2].y);
// }

// static void	debug_new_walls(t_wall *new_wall, t_wall *portal_behind)
// {
// 	printf("NEW WALL BEHIND\n");
// 	printf("left.x %f left.z %f left.ground %f left.ceil %f\n",
// 		new_wall->top.p[1].x, new_wall->top.p[1].z,
// 		new_wall->bottom.p[0].y, new_wall->top.p[1].y);
// 	printf("right.x %f right.z %f right.ground %f right.ceil %f\n",
// 		new_wall->top.p[2].x, new_wall->top.p[2].z,
// 		new_wall->bottom.p[2].y, new_wall->top.p[2].y);
// 	if (!new_wall)
// 		return (0);
// 	printf("NEW PORTAL SIZE BEHIND\n");
// 	printf("left.x %f left.z %f left.ground %f left.ceil %f\n",
// 		portal_behind->top.p[1].x, portal_behind->top.p[1].z,
// 		portal_behind->bottom.p[0].y, portal_behind->top.p[1].y);
// 	printf("right.x %f right.z %f right.ground %f right.ceil %f\n",
// 		portal_behind->top.p[2].x, portal_behind->top.p[2].z,
// 		portal_behind->bottom.p[2].y, portal_behind->top.p[2].y);
// 	printf("----------------------------\n");
// }

static float	calc_new_height(t_wall *current_portal,
				t_wall *portal_behind)
{
	float	max_ground[2];
	float	min_ceiling[2];

	max_ground[0] = ft_fmin(current_portal->bottom.p[0].y,
			current_portal->bottom.p[2].y);
	max_ground[1] = ft_fmin(portal_behind->bottom.p[0].y,
			portal_behind->bottom.p[2].y);
	max_ground[0] = ft_fmax(max_ground[0], max_ground[1]);
	min_ceiling[0] = ft_fmax(current_portal->top.p[1].y,
			current_portal->top.p[2].y);
	min_ceiling[1] = ft_fmax(portal_behind->top.p[1].y,
			portal_behind->top.p[2].y);
	min_ceiling[0] = ft_fmin(min_ceiling[0], min_ceiling[1]);
	return (min_ceiling[0] - max_ground[0]);
}

static Uint32	generate_a_new_lower_wall(t_wall *portal, t_wall *portal_behind)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_wall;

	left.x = portal_behind->bottom.p[0].x;
	right.x = portal_behind->bottom.p[2].x;
	left.y = portal_behind->bottom.p[0].z;
	right.y = portal_behind->bottom.p[2].z;
	left.ceiling = ft_fmax(portal_behind->bottom.p[2].y,
			portal->bottom.p[0].y);
	right.ceiling = ft_fmax(portal_behind->bottom.p[0].y,
			portal->bottom.p[2].y);
	left.ground = portal_behind->bottom.p[0].y;
	right.ground = portal_behind->bottom.p[2].y;
	resize_portal(portal, portal_behind, 'b');
	if (portal->next->top.type < 0 && portal->next->top.type != -door)
		left.idx = portal->next->top.type;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	add_to_middle(&portal_behind, new_wall);
	return (1);
}

static Uint32	generate_a_new_top_wall(t_wall *portal, t_wall *portal_behind)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_wall;

	left.x = portal_behind->top.p[1].x;
	right.x = portal_behind->top.p[2].x;
	left.y = portal_behind->top.p[1].z;
	right.y = portal_behind->top.p[2].z;
	left.ceiling = portal_behind->top.p[2].y;
	right.ceiling = portal_behind->top.p[1].y;
	left.ground = ft_fmin(portal_behind->top.p[1].y, portal->top.p[2].y);
	right.ground = ft_fmin(portal_behind->top.p[2].y, portal->top.p[1].y);
	resize_portal(portal, portal_behind, 't');
	if (portal->next->top.type < 0 && portal->next->top.type != -door)
		left.idx = portal->next->top.type;
	else
		left.idx = -2;
	new_wall = new_point(&left, &right);
	add_to_middle(&portal_behind, new_wall);
	return (1);
}

static t_uint	generate_wall_logic(t_wall *current_portal,
				t_wall *portal_behind)
{
	t_bool	ceil_diff;
	t_bool	floor_diff;
	t_uint	walls;

	ceil_diff = false;
	floor_diff = false;
	walls = 0;
	check_portal_floor_difference(current_portal, portal_behind, &floor_diff);
	check_portal_ceiling_difference(current_portal, portal_behind, &ceil_diff);
	if (floor_diff && !ceil_diff)
		walls += generate_a_new_lower_wall(current_portal, portal_behind);
	if (!floor_diff && ceil_diff)
		walls += generate_a_new_top_wall(current_portal, portal_behind);
	if (ceil_diff && floor_diff)
	{
		walls += generate_a_new_top_wall(current_portal, portal_behind);
		walls += generate_a_new_lower_wall(current_portal, portal_behind);
	}
	if (ceil_diff || floor_diff)
		portal_behind->height = calc_new_height(current_portal, portal_behind);
	return (walls);
}

/*
**	Calculation of extra walls is necessary to handle height differences.
**	2D map is converted to 3D coordinates. When we encounter a portal
**	in map data, that is higher or lower than the next sector, we generate
**	A wall behind that portal.
**	If a door is found, we generate doors to the current sector.
*/
void	calc_extra_walls(t_home *home)
{
	Uint32	i;
	Uint32	j;
	t_wall	*from;
	t_wall	*to;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		from = home->sectors[i]->walls;
		while (j++ < home->sectors[i]->nb_of_walls)
		{
			if (from->top.type >= 0
				&& home->sectors[from->top.type]->is_lift != lift
				&& home->sectors[i]->is_lift != lift)
			{
				to = get_portal_by_idx(i, home->sectors[from->top.type]);
				home->sectors[from->top.type]->nb_of_walls
					+= generate_wall_logic(from, to);
				home->sectors[from->top.type]->nb_of_walls += generate_door(to);
			}
			from = from->next;
		}
		i++;
	}
}
