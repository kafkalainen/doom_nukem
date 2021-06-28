/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_average_unit_normals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:20:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/28 10:23:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	To get the average unit normal vector at a vertex,
**	we take the average of the normals of the neighboring faces.
**	Since the resulting normal should be a unit normal,
**	we can do the averaging by summing all the neighboring normals,
**	and then dividing by the magnitude of this sum.
**	Create a normal[3] set to triangle to store average of
**	neighboring normals.
**	Apply Blinn-Phong's reflection model.
*/

static void	calc_surface_normals(t_sector *sector)
{
	Uint32		i;
	t_wall		*walls;
	t_surface	*ceil_ground;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		walls->top.normal = triangle_normal(&walls->top);
		walls->bottom.normal = triangle_normal(&walls->bottom);
		walls = walls->next;
		i++;
	}
	i = 0;
	ceil_ground = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		ceil_ground->tri.normal = triangle_normal(&ceil_ground->tri);
		ceil_ground = ceil_ground->next;
		i++;
	}
	i = 0;
	ceil_ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		ceil_ground->tri.normal = triangle_normal(&ceil_ground->tri);
		ceil_ground = ceil_ground->next;
		i++;
	}
}

void	calc_average_unit_normals(t_home *home)
{
	Uint32			i;
	t_raster_queue	*queue;

	i = 0;
	queue = create_raster_queue(100);
	while (i < home->nbr_of_sectors)
	{
		calc_surface_normals(home->sectors[i]);
		calc_top_normal_averages(home->sectors[i], queue);
		calc_bottom_normal_averages(home->sectors[i], queue);
		calc_ceiling_normal_averages(home->sectors[i], queue);
		calc_ground_normal_averages(home->sectors[i], queue);
		i++;
	}
	delete_raster_queue(&queue);
}
