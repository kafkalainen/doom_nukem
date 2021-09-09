/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_unit_normals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:20:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_wall_normals(t_sector *sector)
{
	Uint32		i;
	t_wall		*walls;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		walls->top.normal = triangle_normal(&walls->top);
		walls->bottom.normal = triangle_normal(&walls->bottom);
		if (walls->top.type == -door)
		{
			walls->top = translate_triangle(&walls->top,
					vec3_mul(walls->top.normal, -0.05f));
			walls->bottom = translate_triangle(&walls->bottom,
					vec3_mul(walls->bottom.normal, -0.05f));
		}
		walls = walls->next;
		i++;
	}
}

static void	calc_ceil_ground_normals(t_sector *sector)
{
	Uint32		i;
	t_surface	*ceil_ground;

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

void	calc_unit_normals(t_home *home)
{
	Uint32			i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		calc_wall_normals(home->sectors[i]);
		calc_ceil_ground_normals(home->sectors[i]);
		i++;
	}
}
