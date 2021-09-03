/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:55:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 08:10:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	generate_doors(t_wall *current_portal)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_door;

	if (!current_portal->is_door)
		return (0);
	left.x = current_portal->top.p[1].x;
	right.x = current_portal->top.p[2].x;
	left.y = current_portal->top.p[1].z;
	right.y = current_portal->top.p[2].z;
	left.ceiling = current_portal->top.p[1].y;
	right.ceiling = current_portal->top.p[2].y;
	left.ground = current_portal->bottom.p[0].y;
	right.ground = current_portal->bottom.p[2].y;
	left.idx = -door;
	current_portal->is_closed = 1;
	new_door = new_point(&left, &right);
	if (!new_door)
		return (0);
	add_to_middle(&current_portal, new_door);
	return (1);
}
