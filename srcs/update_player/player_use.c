/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:07:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/16 18:08:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	open_door(t_sector *sector, t_xyz look_loc, Uint32 delta_time)
{
	t_wall	*wall;

	(void)delta_time;
	wall = check_if_crossing(sector, look_loc);
	// idx = check_index_of_a_wall(home->sectors[plr->cur_sector], plr->pos, look_dir);
	if (wall && wall->is_door)
		printf("Index of the door is: %d\n", wall->next->top.idx);
	return (1);
}

int		player_use(t_player *plr, t_home *home, Uint32 delta_time)
{
	t_xyz	look_dir;
	t_xyz	look_loc;
	// int		idx;

	if (!plr->input.use)
		return (FALSE);
	look_dir = vec3_unit_vector(plr->look_dir);
	look_loc = vec3_add(plr->pos, look_dir);
	open_door(home->sectors[plr->cur_sector], look_loc, delta_time);
	// else
	// 	printf("it is not crossing!!");
	return (TRUE);
}
