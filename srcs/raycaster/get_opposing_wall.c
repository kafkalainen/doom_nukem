/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opposing_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:58:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/21 11:40:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_point	*get_opposing_wall(t_point *current_wall, unsigned int walls)
{
	t_point			*opposing_wall;
	t_xy			pos;
	t_xy			dir;

	pos.x = (current_wall->next->x0.x + current_wall->x0.x) * 0.5;
	pos.y = (current_wall->next->x0.y + current_wall->x0.y) * 0.5;
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
