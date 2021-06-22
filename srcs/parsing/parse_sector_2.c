/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:29:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 10:48:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_triangles(t_wall *wall, t_point_data *left,
	t_point_data *right)
{
	wall->top.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->top.p[1] = (t_xyz){left->x, left->ceiling, left->y, 1.0f};
	wall->top.p[2] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bottom.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->bottom.p[1] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bottom.p[2] = (t_xyz){right->x, right->ground, right->y, 1.0f};
}

void	add_to_middle(t_wall **current_point, t_wall *new_wall)
{
	t_wall	*temp;

	if (new_wall == NULL)
		return ;
	if (*current_point == NULL)
	{
		*current_point = new_wall;
	}
	else
	{
		temp = (*current_point)->next;
		(*current_point)->next = new_wall;
		new_wall->next = temp;
	}
}
