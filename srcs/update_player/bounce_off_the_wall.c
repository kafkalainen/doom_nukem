/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce_off_the_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 19:31:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	bounce_off_the_wall(t_wall *wall, t_player *plr,
		t_home *home, Uint32 t)
{
	t_xyz	wall_vector;
	t_wall	*new_wall;

	plr->test_pos = vec3_add(plr->pos, vec3_mul(wall->top.normal, t * 0.0005f));
	new_wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, wall_vector);
	if (!new_wall)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos,
			plr->height, home);
		plr->steps += t * 0.005f;
		return (true);
	}
	else
		return (false);
}
