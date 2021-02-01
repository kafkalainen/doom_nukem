/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/01 12:14:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static void		transform_matrix_2d(t_xy pos, t_xy *vertex, float angle)
{
	t_xyz	temp_vertex;

	temp_vertex.x = vertex->x;
	temp_vertex.y = vertex->y;
	vertex->x = cos(angle) * temp_vertex.x - sin(angle) * temp_vertex.y;
	vertex->y = sin(angle) * temp_vertex.x + cos(angle) * temp_vertex.y;
}

static void		translate_matrix_2d(t_xy pos, t_xy *vertex)
{
	t_xy	temp_vertex;

	vertex->x = vertex->x - pos.x;
	vertex->y = vertex->y - pos.y;
}

void			transform_world_view(t_player *plr, t_home *home, float angle)
{
	t_point		*current_point;
	int			i;

	i = 0;
	while (i < 2)
	{
		current_point = home->sectors[i]->points;
		while (current_point)
		{
			transform_matrix_2d(plr->pos, &current_point->x0, angle);
			current_point = current_point->next;
		}
		i++;
	}
}


void			translate_world_view(t_xy step, t_home *home)
{
	t_point		*current_point;
	int			i;

	i = 0;
	while (i < 2)
	{
		current_point = home->sectors[i]->points;
		while (current_point)
		{
			translate_matrix_2d(step, &current_point->x0);
			current_point = current_point->next;
		}
		i++;
	}
}
