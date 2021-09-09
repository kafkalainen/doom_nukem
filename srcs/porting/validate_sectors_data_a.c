/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sectors_data_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:06:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static t_bool	check_valid_connection(t_xyz *p0, t_xyz *p1,
// 			t_sector *sector, int i)
// {
// 	unsigned int	j;
// 	t_wall			*temp;

// 	j = 0;
// 	temp = sector->walls;
// 	while (j < sector->nb_of_walls)
// 	{
// 		if (temp->top.type == i || temp->top.type - DOOR_INDEX == i)
// 		{
// 			if (temp->top.p[1].x == p0->x
// 				&& temp->top.p[1].z == p0->z
// 				&& temp->top.p[2].x == p1->x
// 				&& temp->top.p[2].z == p1->z)
// 				return (true);
// 			else
// 				return (false);
// 		}
// 		j++;
// 		temp = temp->next;
// 	}
// 	return (false);
// }

// static t_bool	check_if_portals_connected(int i, t_home *home)
// {
// 	unsigned int	j;
// 	t_wall			*temp;

// 	j = 0;
// 	temp = home->sectors[i]->walls;
// 	while (j < home->sectors[i]->nb_of_walls)
// 	{
// 		if (temp->top.type >= 0)
// 		{
// 			if (home->nbr_of_sectors == 1)
// 				return (true);
// 			if (temp->top.type >= DOOR_INDEX)
// 			{
// 				if (!(check_valid_connection(&temp->top.p[2], &temp->top.p[1],
// 							home->sectors[temp->top.type - DOOR_INDEX], i)))
// 					return (true);
// 			}
// 			else
// 			{
// 				if (!(check_valid_connection(&temp->top.p[2], &temp->top.p[1],
// 							home->sectors[temp->top.type], i)))
// 					return (true);
// 			}
// 		}
// 		temp = temp->next;
// 		j++;
// 	}
// 	return (false);
// }

// static t_bool	check_if_convex(t_sector *sector)
// {
// 	unsigned int	i;
// 	t_xy			dxy_1;
// 	t_xy			dxy_2;
// 	t_wall			*temp;
// 	int				sign;

// 	i = 0;
// 	temp = sector->walls;
// 	if (sector->nb_of_walls == 3)
// 		return (1);
// 	dxy_1 = vec2_dec(vec2(temp->top.p[2].x, temp->top.p[2].z),
// 			vec2(temp->top.p[0].x, temp->top.p[0].z));
// 	dxy_2 = vec2_dec(vec2(temp->next->top.p[2].x, temp->next->top.p[2].z),
// 			vec2(temp->top.p[2].x, temp->top.p[2].z));
// 	sign = is_negative(vec2_cross(dxy_1, dxy_2));
// 	while (i < sector->nb_of_walls)
// 	{
// 		temp = temp->next;
// 		dxy_1 = dxy_2;
// 		dxy_2 = vec2_dec(vec2(temp->next->top.p[2].x, temp->next->top.p[2].z),
// 				vec2(temp->next->top.p[0].x, temp->next->top.p[0].z));
// 		if (is_negative(vec2_cross(dxy_1, dxy_2)) != sign)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// if (check_if_portals_connected((int)i, home))
// 	map_error_output(3, home);
// if (check_if_convex(home->sectors[i]))
// 	map_error_output(4, home);
int	validate_sectors_data(t_home *home, t_player *plr)
{
	unsigned int	i;

	i = 0;
	if (!(plr_inside(home->sectors[plr->cur_sector], plr)))
		map_error_output(6, home);
	while (i < home->nbr_of_sectors)
	{
		if (home->sectors[i]->nb_of_walls < 3)
			map_error_output(7, home);
		if (check_if_sector_has_same_points(home->sectors[i]))
			map_error_output(2, home);
		i++;
	}
	return (0);
}
