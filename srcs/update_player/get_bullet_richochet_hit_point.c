/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bullet_richochet_hit_point.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:08:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/19 16:01:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	test_triangle(t_triangle *tri, t_bullet_hole *hole_2, float *d,
		t_player *plr)
{
	t_plane	plane;
	t_xyz	hole;
	float	distance;
	float	dot;

	plane.normal = tri->normal;
	plane.point = tri->p[0];
	hole = vec3_intersection_with_ray_and_plane(&plane, plr->pos,
			plr->look_dir);
	dot = vec3_dot_product(vec3_unit_vector(vec3_dec(hole, plr->pos)),
			plr->look_dir);
	if (dot > 0.0f && vec3_is_inside_triangle(tri, hole))
	{
		if (vec3_dot_product(plane.normal, vec3_dec(plane.point, plr->pos)) < 0)
		{
			distance = ft_fabsf(vec3_eucl_dist(vec3_dec(hole, plr->pos)));
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

float	get_ceiling_hit_point(t_sector *sector, t_player *plr,
		t_bullet_hole *hole)
{
	Uint32		i;
	t_surface	*surf;
	float		d;

	i = 0;
	d = 999.0f;
	surf = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		if (test_triangle(&surf->tri, hole, &d, plr))
			hole->sector_idx = sector->idx_sector;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}

float	get_ground_hit_point(t_sector *sector, t_player *plr,
		t_bullet_hole *hole)
{
	Uint32		i;
	t_surface	*surf;
	float		d;

	i = 0;
	d = 999.0f;
	surf = sector->ground;
	while (i < sector->nb_of_ground)
	{
		if (test_triangle(&surf->tri, hole, &d, plr))
			hole->sector_idx = sector->idx_sector;
		surf = surf->next;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}


static t_bullet_hole	loop_through_sector(t_home *home, t_player *plr, unsigned int bullet_sector)
{
	float			d[4];
	t_bullet_hole	hitpoints[4];

	// d[3] = get_entity_hit_point(home, plr, &hitpoints[3], bullet_sector);
	d[2] = get_wall_hit_point(home, plr, &hitpoints[2], bullet_sector);
	d[1] = get_ceiling_hit_point(home->sectors[bullet_sector], plr, &hitpoints[1]);
	d[0] = get_ground_hit_point(home->sectors[bullet_sector], plr, &hitpoints[0]);
	if (d[0] != 999.0f && d[0] <= d[1] && d[0] <= d[2])
	{
		return (hitpoints[0]);
	}
	if (d[1] != 999.0f && d[1] <= d[0] && d[1] <= d[2])
	{
		return (hitpoints[1]);
	}
	if (d[2] != 999.0f && d[2] <= d[1] && d[2] <= d[0])
	{
		return (hitpoints[2]);
	}
	return (hitpoints[0]);
}

float	get_wall_hit_point(t_home *home, t_player *plr, t_bullet_hole *hole,
		unsigned int bullet_sector)
{
	Uint32		i;
	t_wall		*wall;
	float		d;

	i = 0;
	d = 999.0f;
	wall = home->sectors[bullet_sector]->walls;
	while (i < home->sectors[bullet_sector]->nb_of_walls)
	{
		if (test_triangle(&wall->top, hole, &d, plr))
		{
			if (wall->top.idx >= 0)
			{
				*hole = loop_through_sector(home, plr, wall->top.idx);
				break ;
			}
			else
				hole->sector_idx = bullet_sector;
		}
		if (test_triangle(&wall->bottom, hole, &d, plr))
		{
			if (wall->bottom.idx >= 0)
			{
				*hole = loop_through_sector(home, plr, wall->bottom.idx);
				break ;
			}
			else
				hole->sector_idx = bullet_sector;
		}
		wall = wall->next;
		i++;
	}
	return (d);
}

void	get_bullet_ricochet_hit_point(t_home *home, t_player *plr,
		unsigned int bullet_sector)
{
	t_bullet_hole	hole;
	t_projectile	*current;

	current = home->projectile_pool[home->projectile_idx];
	hole = loop_through_sector(home, plr, bullet_sector);
	hole.point = translate_point(&hole.point, vec3_mul(hole.normal, 0.15f));
	current->pos = hole.point;
	current->top = rotate_triangle(&current->top, vec3_angle(hole.normal, current->normal), 'y');
	current->bot = rotate_triangle(&current->bot, vec3_angle(hole.normal, current->normal), 'y');
	current->top.normal = hole.normal;
	current->bot.normal = hole.normal;
	current->sector_idx = hole.sector_idx;
	printf("%d\n", current->sector_idx);
}
