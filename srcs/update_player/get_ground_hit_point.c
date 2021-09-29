/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ground_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 09:26:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 15:18:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_ground_hit_point(t_sector *sector, t_ray *ray,
		t_bullet_hole *hole)
{
	Uint32		i;
	t_surface	*surf;
	float		d;

	i = 0;
	d = 400000000.0f;
	surf = sector->ground;
	hole->hole_type = nothing;
	while (i < sector->nb_of_ground)
	{
		if (test_triangle(&surf->tri, hole, &d, ray))
		{
			hole->hole_type = ground_hole;
			hole->sector_idx = sector->idx_sector;
		}
		surf = surf->next;
		i++;
	}
	return (d);
}
