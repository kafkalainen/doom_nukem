/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_centroid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:03:31 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 10:18:07 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	editor_calculate_centroid(t_editor_sector *sector)
{
	int				i;
	t_xy			centroid;
	t_editor_walls	*cur_wall;

	i = 0;
	centroid = vec2(0.0f, 0.0f);
	cur_wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		centroid.x += cur_wall->x0.x;
		centroid.y += cur_wall->x0.y;
		i++;
		cur_wall = cur_wall->next;
	}
	centroid = vec2_div(centroid, sector->nb_of_walls);
	return (centroid);
}

t_xy	calculate_centroid(t_sector *sector)
{
	t_uint			i;
	t_xy			centroid;
	t_wall			*cur_wall;

	i = 0;
	centroid = vec2(0.0f, 0.0f);
	cur_wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		centroid.x += cur_wall->point.x;
		centroid.y += cur_wall->point.y;
		i++;
		cur_wall = cur_wall->next;
	}
	centroid = vec2_div(centroid, sector->nb_of_walls);
	return (centroid);
}
