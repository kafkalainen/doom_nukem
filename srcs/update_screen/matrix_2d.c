/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/21 16:55:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


void			transform_world_view(t_home *home, float delta_dir)
{
	t_point			*current_point;
	unsigned int	i;
	unsigned int	walls;

	i = 0;
	while (i < home->nbr_of_sectors)
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
	t_point			*current_point;
	unsigned int	i;
	unsigned int	walls;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		walls = home->sectors[i]->nb_of_walls;
		current_point = home->sectors[i]->points;
		while (walls)
		{
			current_point->x0 = vec2_dec(current_point->x0, step);
			current_point = current_point->next;
			walls--;
		}
		i++;
	}
}
