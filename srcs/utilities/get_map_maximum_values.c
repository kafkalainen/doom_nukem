/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_maximum_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:30:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 14:37:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	wall_logic(t_wall *wall, t_xyz *min, t_xyz *max)
{
	if (wall->top.p[0].y < min->y)
		min->y = wall->top.p[0].y;
	if (wall->top.p[1].y > max->y)
		max->y = wall->top.p[1].y;
	if (wall->top.p[0].x < min->x)
		min->x = wall->top.p[0].x;
	if (wall->top.p[0].x > max->x)
		max->x = wall->top.p[0].x;
	if (wall->top.p[0].z < min->z)
		min->z = wall->top.p[0].z;
	if (wall->top.p[0].z > max->z)
		max->z = wall->top.p[0].z;
}

static float	get_highest_value(t_xyz min, t_xyz max)
{
	max.x = ft_fabsf(max.x - min.x);
	max.y = ft_fabsf(max.y - min.y);
	max.z = ft_fabsf(max.z - min.z);
	if (max.x >= max.y && max.x >= max.z)
		return (max.x);
	if (max.y >= max.x && max.y >= max.z)
		return (max.y);
	if (max.z >= max.x && max.z >= max.y)
		return (max.z);
	return (max.x);
}

void	get_map_maximum_values(float *res, t_sector **sectors,
		t_uint nb_of_sectors)
{
	t_xyz	min;
	t_xyz	max;
	t_wall	*wall;
	t_uint	i;

	min = vec3(5000.0f, 5000.0f, 100.0f);
	max = vec3(-5000.0f, -5000.0f, -100.0f);
	while (nb_of_sectors--)
	{
		wall = sectors[nb_of_sectors]->walls;
		i = 0;
		while (i < sectors[nb_of_sectors]->nb_of_walls)
		{
			wall_logic(wall, &min, &max);
			wall = wall->next;
			i++;
		}
	}
	*res = get_highest_value(min, max);
}
