/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/01 11:34:07 by jnivala          ###   ########.fr       */
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
	t_polygon	*x0;
	int			i;

	i = 0;
	while (i < 2)
	{
		x0 = home->sectors[i]->polygons;
		while (x0)
		{
			transform_matrix_2d(plr->pos, &x0->x0, angle);
			x0 = x0->next;
		}
		i++;
	}
}


void			translate_world_view(t_xy step, t_home *home)
{
	t_polygon	*x0;
	int			i;

	i = 0;
	while (i < 2)
	{
		x0 = home->sectors[i]->polygons;
		while (x0)
		{
			translate_matrix_2d(step, &x0->x0);
			x0 = x0->next;
		}
		i++;
	}
}
