/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling_hit_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 09:26:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/24 09:26:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
		{
			hole->sector_idx = sector->idx_sector;
			hole->hole_type = ceiling_hole;
		}
		surf = surf->next;
		i++;
	}
	return (d);
}
