/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bullet_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:08:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	test_triangle(t_triangle *tri, t_bullet_hole *hole_2, float *d,
		t_ray *ray)
{
	t_plane	plane;
	t_xyz	hole;
	float	distance;
	float	dot;

	plane = (t_plane){tri->p[0], tri->normal};
	hole = vec3_intersection_with_ray_and_plane(&plane, ray->pos, ray->dir);
	dot = vec3_dot_product(vec3_unit_vector(vec3_dec(hole, ray->pos)),
			ray->dir);
	if (dot > 0.0f && vec3_is_inside_triangle(tri, hole))
	{
		if (vec3_dot_product(plane.normal, vec3_dec(plane.point, ray->pos)) < 0)
		{
			distance = get_distance_squared(hole, ray->pos);
			if (distance < *d)
			{
				*d = distance;
				hole_2->point = hole;
				hole_2->normal = tri->normal;
				return (1);
			}
		}
	}
	return (0);
}

static t_bullet_hole	loop_through_sector(t_home *home, t_ray *ray,
		int bullet_sector)
{
	float			d[4];
	t_bullet_hole	hitpoints[4];

	d[0] = get_ground_hit_point(home->sectors[bullet_sector], ray,
			&hitpoints[0]);
	d[1] = get_ceiling_hit_point(home->sectors[bullet_sector], ray,
			&hitpoints[1]);
	if (ray->side == ENEMY)
		d[3] = get_player_hit_point(ray, &hitpoints[3], bullet_sector);
	else if (ray->side == PLAYER)
		d[3] = get_entity_hit_point(home, ray, &hitpoints[3], bullet_sector);
	else
		d[3] = 9999.0f;
	d[2] = get_wall_hit_point(home, ray, &hitpoints[2], bullet_sector);
	if (d[0] != 9999.0f && d[0] <= d[1] && d[0] <= d[2] && d[0] <= d[3])
		return (hitpoints[0]);
	if (d[1] != 9999.0f && d[1] <= d[0] && d[1] <= d[2] && d[1] <= d[3])
		return (hitpoints[1]);
	if (d[2] != 9999.0f && d[2] <= d[1] && d[2] <= d[0] && d[2] <= d[3])
		return (hitpoints[2]);
	if (d[3] != 9999.0f && d[3] <= d[1] && d[3] <= d[0] && d[3] <= d[2])
		return (hitpoints[3]);
	return (hitpoints[0]);
}

static void	set_hole_properties(int *hole_type, int *sector_idx, int cur_sector)
{
	*hole_type = wall_hole;
	*sector_idx = cur_sector;
}

float	get_wall_hit_point(t_home *home, t_ray *ray, t_bullet_hole *hole,
		int bullet_sector)
{
	Uint32		i;
	t_wall		*wall;
	float		d;

	i = 0;
	d = 999.0f;
	wall = home->sectors[bullet_sector]->walls;
	while (i < home->sectors[bullet_sector]->nb_of_walls)
	{
		if (test_triangle(&wall->top, hole, &d, ray)
			|| test_triangle(&wall->bottom, hole, &d, ray))
		{
			if (check_if_open_portal(wall))
			{
				*hole = loop_through_sector(home, ray, wall->top.type);
				break ;
			}
			else
				set_hole_properties(&hole->hole_type, &hole->sector_idx,
					bullet_sector);
		}
		wall = wall->next;
		i++;
	}
	return (d);
}

t_bullet_hole	get_bullet_hit_point(t_home *home, t_ray *ray,
		int bullet_sector)
{
	t_bullet_hole	hole;

	hole = loop_through_sector(home, ray, bullet_sector);
	hole.point = translate_point(&hole.point, vec3_mul(hole.normal, 0.15f));
	return (hole);
}
