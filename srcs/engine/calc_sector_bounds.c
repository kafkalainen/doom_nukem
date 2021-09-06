/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sector_bounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 08:13:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	find_biggest_square(t_sector *sector)
{
	size_t	walls;
	t_wall	*temp;

	walls = sector->nb_of_walls;
	temp = sector->walls;
	while (walls)
	{
		if (temp->top.p[0].x < sector->bounding_box.top_left.x)
			sector->bounding_box.top_left.x = temp->top.p[0].x;
		if (temp->top.p[0].x > sector->bounding_box.top_right.x)
			sector->bounding_box.top_right.x = temp->top.p[0].x;
		if (temp->top.p[0].z < sector->bounding_box.top_left.y)
			sector->bounding_box.top_left.y = temp->top.p[0].z;
		if (temp->top.p[0].z > sector->bounding_box.bottom_left.y)
			sector->bounding_box.bottom_left.y = temp->top.p[0].z;
		temp = temp->next;
		walls--;
	}
	sector->bounding_box.top_right.y = sector->bounding_box.top_left.y;
	sector->bounding_box.bottom_right.y = sector->bounding_box.bottom_left.y;
	sector->bounding_box.bottom_right.x = sector->bounding_box.top_right.x;
	sector->bounding_box.bottom_left.x = sector->bounding_box.top_left.x;
}

void	calc_sector_bounds(t_sector *sector)
{
	sector->bounding_box.top_left = vec2(sector->walls->top.p[0].x,
			sector->walls->top.p[0].z);
	sector->bounding_box.top_right = vec2(sector->walls->top.p[0].x,
			sector->walls->top.p[0].z);
	sector->bounding_box.bottom_left = vec2(sector->walls->top.p[0].x,
			sector->walls->top.p[0].z);
	sector->bounding_box.bottom_right = vec2(sector->walls->top.p[0].x,
			sector->walls->top.p[0].z);
	find_biggest_square(sector);
}
