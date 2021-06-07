/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_and_floor_properties.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:13:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/07 16:27:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_wall_facing(t_wall *wall)
{
	if (wall->normal.x < 0)
		wall->wall_facing = vec2_ang(wall->normal, (t_xy){0, 1}) + PI;
	if (wall->wall_facing == 0.0f)
		wall->wall_facing = 2 * PI;
	wall->wall_facing = INV_PI_BY_TWO * wall->wall_facing;
	if (wall->wall_facing < 0.2f)
		wall->wall_facing = 0.2f;
}

void	calc_wall_and_floor_properties(t_home *home)
{
	unsigned int	i;
	unsigned int	j;
	t_wall			*temp;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		temp = home->sectors[i]->walls;
		// calc_sector_bounds(home->sectors[i]);
		triangulate_floor(home->sectors[i], 'g');
		// triangulate_ceiling(home->sectors[i], 'c');
		while (j < home->sectors[i]->nb_of_walls)
		{
			temp->normal = vec2_normal(vec3_to_vec2(temp->top.p[0]), vec3_to_vec2(temp->top.p[2]));
			temp->wall_facing = vec2_ang(temp->normal, (t_xy){0, 1});
			check_wall_facing(temp);
			temp = temp->next;
			j++;
		}
		i++;
	}
	// calc_slanted_floors(home);
	// precalc_ground_texels(home);
}
