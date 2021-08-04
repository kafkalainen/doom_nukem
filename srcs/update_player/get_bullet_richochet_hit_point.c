/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bullet_richochet_hit_point.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:08:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/04 11:00:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	test_triangle(t_triangle *tri, t_xyz *isection_2, float *d,
		t_player *plr)
{
	t_plane	plane;
	t_xyz	isection;
	float	distance;
	float	dot;

	plane.normal = tri->normal;
	plane.point = tri->p[0];
	isection = vec3_intersection_with_ray_and_plane(&plane, plr->pos,
			plr->look_dir);
	dot = vec3_dot_product(vec3_unit_vector(vec3_dec(isection, plr->pos)),
			plr->look_dir);
	if (dot > 0.0f && vec3_is_inside_triangle(tri, isection))
	{
		distance = ft_fabsf(vec3_eucl_dist(vec3_dec(isection, plr->pos)));
		if (distance < *d)
		{
			*d = distance;
			*isection_2 = isection;
			return (1);
		}
	}
	return (0);
}

float	get_ceiling_hit_point(t_sector *sector, t_player *plr,
		t_xyz *isection)
{
	Uint32		i;
	t_surface	*surf;
	float		d;

	i = 0;
	d = 999.0f;
	surf = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		test_triangle(&surf->tri, isection, &d, plr);
		surf = surf->next;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}

float	get_ground_hit_point(t_sector *sector, t_player *plr,
		t_xyz *isection)
{
	Uint32		i;
	t_surface	*surf;
	float		d;

	i = 0;
	d = 999.0f;
	surf = sector->ground;
	while (i < sector->nb_of_ground)
	{
		test_triangle(&surf->tri, isection, &d, plr);
		surf = surf->next;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}

float	get_wall_hit_point(t_home *home, t_player *plr, t_xyz *isection,
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
		if (test_triangle(&wall->top, isection, &d, plr)
			&& wall->top.idx >= 0)
			get_bullet_ricochet_hit_point(home, plr, bullet_sector);
		if (test_triangle(&wall->bottom, isection, &d, plr)
			&& wall->bottom.idx >= 0)
			get_bullet_ricochet_hit_point(home, plr, bullet_sector);
		wall = wall->next;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}

t_xyz	get_bullet_ricochet_hit_point(t_home *home, t_player *plr,
		unsigned int bullet_sector)
{
	float	d[3];
	t_xyz	hitpoints[3];

	d[2] = get_wall_hit_point(home, plr, &hitpoints[2], bullet_sector);
	d[1] = get_ceiling_hit_point(home->sectors[bullet_sector], plr, &hitpoints[1]);
	d[0] = get_ground_hit_point(home->sectors[bullet_sector], plr, &hitpoints[0]);
	ft_putstr("BULLET SECTOR ");
	ft_putendl(ft_itoa(bullet_sector));
	if (d[0] != 999.0f && d[0] <= d[1] && d[0] <= d[2])
		home->entity_pool[1]->pos = hitpoints[0];
	if (d[1] != 999.0f && d[1] <= d[0] && d[1] <= d[2])
		home->entity_pool[1]->pos = hitpoints[1];
	if (d[2] != 999.0f && d[2] <= d[1] && d[2] <= d[0])
		home->entity_pool[1]->pos = hitpoints[2];
	return (hitpoints[2]);
}
