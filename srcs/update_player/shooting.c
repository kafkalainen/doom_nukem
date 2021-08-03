/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:12:34 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/03 15:40:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void		test_triangle(t_triangle *tri, t_xyz *isection_2, float *d, t_player *plr)
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
		}
	}
}

static float	get_ceiling_hit_point(t_sector *sector, t_player *plr, t_xyz *isection)
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

static float	get_ground_hit_point(t_sector *sector, t_player *plr, t_xyz *isection)
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

static float	get_wall_hit_point(t_sector *sector, t_player *plr, t_xyz *isection)
{
	Uint32		i;
	t_wall		*wall;
	float		d;

	i = 0;
	d = 999.0f;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		test_triangle(&wall->top, isection, &d, plr);
		test_triangle(&wall->bottom, isection, &d, plr);
		wall = wall->next;
		i++;
	}
	if (d != 999.0f)
		return (d);
	else
		return (999.0f);
}

static t_xyz	get_bullet_hit_point(t_sector *sector, t_player *plr)
{
	float	d[3];
	t_xyz	hitpoints[3];

	d[0] = get_ground_hit_point(sector, plr, &hitpoints[0]);
	d[1] = get_ceiling_hit_point(sector, plr, &hitpoints[1]);
	d[2] = get_wall_hit_point(sector, plr, &hitpoints[2]);
	if (d[0] != 999.0f && d[0] <= d[1] && d[0] <= d[2])
		ft_putendl("HIT A GROUND.");
	if (d[1] != 999.0f && d[1] <= d[0] && d[1] <= d[2])
		ft_putendl("HIT A CEILING.");
	if (d[2] != 999.0f && d[2] <= d[1] && d[2] <= d[0])
		ft_putendl("HIT A WALL.");
	return (hitpoints[2]);
}

void			shooting_handle(t_home *home, t_player *plr)
{
//	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	get_bullet_hit_point(home->sectors[plr->cur_sector], plr);
}
