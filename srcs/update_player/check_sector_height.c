/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector_height.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:55:35 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/04 10:51:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_vertically_possible(t_home *home, t_player *plr, t_xyz pos)
{
	int		idx;
	t_xyz	ceiling;
	t_xyz	isection;

	idx = find_current_sector(home, pos, plr->cur_sector, &isection);
	if (idx == -1)
		return (false);
	get_ceiling_intersection(home->sectors[idx], pos, &ceiling);
	if (plr->height <= (ceiling.y - isection.y))
		return (true);
	return (false);
}
