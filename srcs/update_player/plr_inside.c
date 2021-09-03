/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_inside.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 08:57:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 15:20:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	plr_inside(t_sector *sector, t_player *plr)
{
	t_wall		*wall;
	Uint32		i;
	t_xy		pos;
	t_xy		dir;
	Uint32		walls_crossed;

	i = 0;
	walls_crossed = 0;
	wall = sector->walls;
	pos = vec3_to_vec2(plr->pos);
	dir = (t_xy){0.0f, -20000.0f};
	dir = vec2_dec(dir, pos);
	while (i < sector->nb_of_walls)
	{
		walls_crossed += check_intersection(wall, pos, dir);
		wall = wall->next;
		i++;
	}
	return (walls_crossed % 2);
}
