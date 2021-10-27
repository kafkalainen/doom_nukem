/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:38:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 14:49:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_player_hit_point(t_home *home, t_ray *ray, t_bullet_hole *hole,
		int bullet_sector)
{
	float		d[2];
	t_plane		plr_plane;
	t_xyz		isection;

	d[0] = 400000000.0f;
	d[1] = 400000000.0f;
	hole->type = nothing;
	plr_plane = (t_plane){ray->plr_pos, vec3_unit_vector(vec3_dec(ray->pos,
				ray->plr_pos))};
	if (bullet_sector == ray->end_sector)
	{
		isection = vec3_intersection_with_ray_and_plane(&plr_plane,
				ray->pos, ray->dir);
		d[0] = get_distance_squared(ray->plr_pos, isection);
		d[1] = get_poster_hit_point(home, ray, hole, bullet_sector);
	}
	if (d[0] <= 1.0f)
	{
		hole->type = player;
		hole->sector_idx = bullet_sector;
	}
	return (d[0]);
}
