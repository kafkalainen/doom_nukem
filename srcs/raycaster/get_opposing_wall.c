/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opposing_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:58:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/01 14:58:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	ADJUZTED
*/
t_wall	*get_opposing_wall(t_wall *current_wall, unsigned int walls)
{
	t_wall			*opposing_wall;
	t_xy			pos;
	t_xy			dir;

	pos.x = (current_wall->top.p[2].x + current_wall->top.p[0].x) * 0.5;
	pos.y = (current_wall->top.p[2].z + current_wall->top.p[0].z) * 0.5;
	dir = vec2_mul(current_wall->normal, 20000.0f);
	dir = vec2(-dir.x, -dir.y);
	opposing_wall = current_wall->next;
	while (walls - 1)
	{
		if (check_if_lseg_intersects(opposing_wall, &pos, &dir))
			break ;
		opposing_wall = opposing_wall->next;
		walls--;
	}
	return (opposing_wall);
}
