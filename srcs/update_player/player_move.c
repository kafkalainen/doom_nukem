/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:26 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/01 16:33:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*check_if_crossing(t_sector *sector, t_xyz pos)
{
	unsigned int	i;
	t_wall			*temp;

	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (vec3_signed_distance_to_plane(pos, temp->top.normal, temp->top.p[0]))
			return (temp);
		temp = temp->next;
		i++;
	}
	return (NULL);
}

t_xyz	check_y(t_sector *sector, t_player *plr, t_xyz pos)
{
	unsigned int	i;
	t_surface		*ground;
	t_xyz			dir;
	t_plane			plane;

	i = 0;
	dir = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (point_inside_a_triangle_surface(ground->tri.p[0],
				ground->tri.p[1], ground->tri.p[2], pos))
			break ;
		ground = ground->next;
		i++;
	}
	plane.point = ground->tri.p[0];
	plane.normal = ground->tri.normal;
	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	pos.y += plr->height;
	return (pos);
}

// void	add_motion(t_xyz *pos, Uint32 delta_time)
// {
// 	static Uint32	time = 0;
// 	static Uint32	move_left = 0;
// 	static Uint32	move_right = 0;

// 	if (time < 300 && move_left)
// 	{
// 		time += delta_time;
// 		pos->x -= 1.0f;
// 	}
// 	else if (time >= 300 && move_left)
// 	{
// 		move_right = 1;
// 		time = 0;
// 	}
// 	else if (time < 300 && move_right)
// 	{
// 		time += delta_time;
// 		pos->x += 1.0f;
// 	}
// 	else if (time >= 300 && move_right)
// 	{
// 		move_right = 1;
// 		time = 0;
// 	}
// 	else
// 		*pos = *pos;
// }

int	plr_inside(t_sector *sector, t_player *plr)
{
	t_wall	*wall;
	Uint32		i;
	t_xy	pos;
	t_xy	dir;
	Uint32	walls_crossed;

	i = 0;
	walls_crossed = 0;
	wall = sector->walls;
	pos = vec3_to_vec2(plr->pos);
	dir = (t_xy){0.0f, -20000.0f};
	dir = vec2_dec(dir, pos);
	while (i < sector->nb_of_walls)
	{
		walls_crossed += check_intersection(wall, pos, dir);
		wall = wall->next;
		i++;
	}
	return (walls_crossed % 2);
}

int	player_move(t_player *plr, t_home *home, Uint32 t)
{
	t_wall			*wall;
	t_xyz			new_loc;
	float			dist;

	plr->move_dir.y = 0.0f;
	plr->move_dir = vec3_unit_vector(plr->move_dir);
	new_loc = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.01f));
	if (check_distance_to_ceiling(home->sectors[plr->cur_sector], &new_loc))
		return (FALSE);
	wall = check_if_crossing(home->sectors[plr->cur_sector], new_loc);
	if (wall)
	{
		if (wall->top.idx >= 0)
		{
			if (check_y_diff(plr, &new_loc, home->sectors[wall->top.idx]))
				return (FALSE);
			if ((wall->is_door && !wall->is_closed) || !wall->is_door)
			{
				plr->cur_sector = wall->top.idx;
				home->sectors[plr->cur_sector]->lights.state = TRUE;
			 	plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
				return (TRUE);
			}
		}
		else
			return (FALSE);
	}
	else
	{
		plr->pos = vec3_add(plr->pos, vec3_mul(plr->move_dir, t * 0.005f));
		dist = check_distance_to_ground(home->sectors[plr->cur_sector], plr, plr->pos);
		if (dist < 0 && dist > -plr->height)
			plr->pos.y -= dist;
		// add_motion(&plr->pos, t);
		return (TRUE);
	}
	return (FALSE);
}
