/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:26:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/09 13:26:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	find_path(t_home *home, int cur, int dest, int *sector_count)
{
	t_uint	i;
	t_wall	*portal;

	i = 0;
	portal = home->sectors[cur]->walls;
	*(home->sector_buffer + *sector_count) = cur;
	*sector_count += 1;
	while (i < home->sectors[cur]->nb_of_walls)
	{
		if (check_if_open_portal(portal)
			&& !check_if_already_been_in_this_sector(portal->top.type,
				home->sector_buffer, *sector_count))
		{
			if (portal->top.type == dest)
				return (true);
			else
			{
				if (find_path(home, portal->top.type, dest, sector_count))
					return (true);
			}
		}
		portal = portal->next;
		i++;
	}
	return (false);
}
