/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_norm_vectors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:13:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 19:16:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		calc_normal_vectors(t_home *home)
{
	unsigned int	i;
	unsigned int	j;
	t_point			*temp;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		temp = home->sectors[i]->points;
		while (j < home->sectors[i]->nb_of_walls)
		{
			temp->normal = vec2_normal(temp->x0, temp->next->x0);
			temp->wall_facing = vec2_ang(temp->normal, (t_xy){0, 1});
			if (temp->normal.x < 0)
				temp->wall_facing = vec2_ang(temp->normal, (t_xy){0, 1}) + PI;
			if (temp->wall_facing == 0.0f)
				temp->wall_facing = 2 * PI;
			temp->wall_facing = INV_PI_BY_TWO * temp->wall_facing;
			if (temp->wall_facing < 0.2f)
				temp->wall_facing = 0.2f;
			temp = temp->next;
			j++;
		}
		i++;
	}
}
