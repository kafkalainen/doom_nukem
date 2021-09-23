/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:55:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 08:48:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	generate_door(t_wall *portal)
{
	t_point_data	left;
	t_point_data	right;
	t_wall			*new_door;

	if (!portal->is_door)
		return (0);
	left.x = portal->top.p[1].x;
	right.x = portal->top.p[2].x;
	left.y = portal->top.p[1].z;
	right.y = portal->top.p[2].z;
	left.ceiling = portal->top.p[1].y;
	right.ceiling = portal->top.p[2].y;
	left.ground = portal->bottom.p[0].y;
	right.ground = portal->bottom.p[2].y;
	left.idx = -door;
	portal->is_closed = 1;
	new_door = new_point(&left, &right);
	if (!new_door)
		return (0);
	add_to_middle(&portal, new_door);
	return (1);
}
