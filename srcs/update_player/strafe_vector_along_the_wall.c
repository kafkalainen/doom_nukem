/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe_vector_along_the_wall.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:54:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 15:21:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	strafe_along_the_wall(t_wall *wall, t_player *plr,
		t_home *home, Uint32 t)
{
	float	angle;
	t_xyz	wall_vector;
	t_wall	*new_wall;

	wall_vector = vec3_unit_vector(vec3_dec(wall->bottom.p[0],
				wall->bottom.p[2]));
	angle = vec3_angle(plr->move_dir, wall_vector);
	if (angle < 1.57f && angle >= 0.0f)
		wall_vector = wall_vector;
	else
		wall_vector = vec3_mul(wall_vector, -1.0);
	plr->test_pos = vec3_add(plr->pos, vec3_mul(wall_vector, t * 0.0005f));
	new_wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
			plr->width, plr->test_pos, wall_vector);
	if (!new_wall)
	{
		plr->pos = plr->test_pos;
		check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
		plr->steps += t * 0.005f;
		return (TRUE);
	}
	else
		return (FALSE);
}
