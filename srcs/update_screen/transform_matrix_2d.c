/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/12 11:07:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			transform_world_view(t_home *home, float delta_dir)
{
	t_point		*current_point;
	int			i;
	int			walls;

	i = 0;
	while (i < home->nb_of_sectors)
	{
		walls = home->sectors[i]->nb_of_walls;
		current_point = home->sectors[i]->points;
		while (walls)
		{
			current_point->x0 = vec2_rot(current_point->x0, delta_dir);
			current_point = current_point->next;
			walls--;
		}
		i++;
	}
}


void			translate_world_view(t_home *home, t_xy step)
{
	t_point		*current_point;
	int			i;
	int			walls;

	i = 0;
	while (i < home->nb_of_sectors)
	{
		current_point = home->sectors[i]->points;
		walls = home->sectors[i]->nb_of_walls;
		while (walls)
		{
			current_point->x0 = vec2_dec(current_point->x0, step);
			current_point = current_point->next;
			walls--;
		}
		i++;
	}
}
