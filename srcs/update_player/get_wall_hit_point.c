/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_hit_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:40:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 12:35:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_hole_properties(t_wall *wall, int *hole_type, int *sector_idx,
			int cur_sector)
{
	if (wall->is_door)
		*hole_type = nothing;
	else
		*hole_type = wall_hole;
	*sector_idx = cur_sector;
}

float	get_wall_hit_point(t_home *home, t_ray *ray, t_bullet_hole *hole,
		int sector)
{
	t_uint			i;
	t_wall			*wall;
	float			d[2];
	t_bool			test[3];

	i = 0;
	d[0] = 400000000.0f;
	d[1] = 400000000.0f;
	hole->type = nothing;
	wall = home->sectors[sector]->walls;
	while (i++ < home->sectors[sector]->nb_of_walls)
	{
		test[0] = test_ray(&wall->top, hole, &d[0], ray);
		test[1] = test_ray(&wall->bot, hole, &d[1], ray);
		test[2] = check_if_open_portal(wall);
		if ((test[2] && test[0]) || (test[2] && test[1]))
		{
			*hole = loop_through_sector(home, ray, wall->top.type);
			break ;
		}
		else if (test[0] || test[1])
			set_hole_properties(wall, &hole->type, &hole->sector_idx, sector);
		wall = wall->next;
	}
	return (ft_fmin(d[0], d[1]));
}
