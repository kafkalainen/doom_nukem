/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sector_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 20:44:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	find_biggest_square(t_sector *sector)
{
	size_t	walls;
	t_point	*temp;

	walls = sector->nb_of_walls;
	temp = sector->points;
	while (walls)
	{
		if (temp->x0.x < sector->floor_top_left.x)
			sector->floor_top_left.x = temp->x0.x;
		if (temp->x0.x > sector->floor_top_right.x)
			sector->floor_top_right.x = temp->x0.x;
		if (temp->x0.y < sector->floor_top_left.y)
			sector->floor_top_left.y = temp->x0.y;
		if (temp->x0.y > sector->floor_bottom_left.y)
			sector->floor_bottom_left.y = temp->x0.y;
		temp = temp->next;
		walls--;
	}
	sector->floor_top_right.y = sector->floor_top_left.y;
	sector->floor_bottom_right.y = sector->floor_bottom_left.y;
	sector->floor_bottom_right.x = sector->floor_top_right.x;
	sector->floor_bottom_left.x = sector->floor_top_left.x;
}

/*
**	Calc_sector texels needs to happen before any
**	translation or transformation matrix is applied.
*/

void	calc_sector_texels(t_sector *sector)
{
	sector->floor_top_left = vec3(sector->points->x0.x,
			sector->points->x0.y, 0.0f);
	sector->floor_top_right = vec3(sector->points->x0.x,
			sector->points->x0.y, 0.0f);
	sector->floor_bottom_left = vec3(sector->points->x0.x,
			sector->points->x0.y, 0.0f);
	sector->floor_bottom_right = vec3(sector->points->x0.x,
			sector->points->x0.y, 0.0f);
	find_biggest_square(sector);
}
