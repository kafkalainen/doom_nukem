/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/05 13:35:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			transform_world_view(t_home *home, float delta_dir)
{
	t_point		*current_point;
	int			i;

	i = 0;
	while (i < 2)
	{
		current_point = home->sectors[i]->points;
		while (current_point)
		{
			current_point->x0 = vec2_rot(current_point->x0, delta_dir);
			current_point = current_point->next;
		}
		i++;
	}
}


void			translate_world_view(t_home *home, t_xy step)
{
	t_point		*current_point;
	int			i;

	i = 0;
	while (i < 2)
	{
		current_point = home->sectors[i]->points;
		while (current_point)
		{
			current_point->x0 = vec2_dec(current_point->x0, step);
			current_point = current_point->next;
		}
		i++;
	}
}
