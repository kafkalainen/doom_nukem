/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sector_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/19 10:36:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		calc_floor_distances(t_sector *sector)
{
	sector->floor_top_right.x = sector->floor_top_right.x
		- sector->floor_top_left.x;
	sector->floor_bottom_right.x = sector->floor_bottom_right.x
		- sector->floor_bottom_left.x;
	sector->floor_bottom_right.y = sector->floor_bottom_right.y
		- sector->floor_top_right.y;
	sector->floor_bottom_left.y = sector->floor_bottom_left.y
		- sector->floor_top_left.y;
	sector->floor_bottom_left.x = 0.0f;
	sector->floor_top_left.x = 0.0f;
	sector->floor_top_left.y = 0.0f;
	sector->floor_top_right.y = 0.0f;
}

static void		find_biggest_square(t_sector *sector)
{
	size_t		walls;
	t_point		*temp;

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

static void		map_texture_to_floor(t_sector *sector, t_frame *frame, t_home *home)
{
	t_texture *tex;

	tex = get_tex(sector->tex_floor, home->editor_tex);
	sector->floor_top_left.x = sector->floor_bottom_right.x / tex->w;
	sector->floor_top_right.x = sector->floor_top_right.x / tex->w;
	sector->floor_bottom_left.y = sector->floor_bottom_left.y / tex->h;
	sector->floor_bottom_right.y = sector->floor_bottom_right.y / tex->h;
	sector->floor_bottom_right.x = sector->floor_bottom_right.x / tex->w;
}

/*
**	Calc_sector texels needs to happen before any translation or transformation matrix is applied.
*/
void			calc_sector_texels(t_sector *sector, t_frame *frame, t_home *home)
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
	calc_floor_distances(sector);
	map_texture_to_floor(sector, frame, home);
}
