/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sectors_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:06:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/08 08:38:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	check_valid_connection(t_xyz *p0, t_xyz *p1, t_sector *sector, int i)
{
	unsigned int	j;
	t_wall			*temp;

	j = 0;
	temp = sector->walls;
	while (j < sector->nb_of_walls)
	{
		if (temp->top.idx == i)
		{
			if (temp->top.p[0].x == p0->x
				&& temp->top.p[0].z == p0->z
				&& temp->top.p[2].x == p1->x
				&& temp->top.p[2].z == p1->z)
				return (1);
			else
				return (0);
		}
		j++;
		temp = temp->next;
	}
	return (0);
}

static int	check_if_portals_connected(int i, t_home *home)
{
	unsigned int	j;
	t_wall			*temp;

	j = 0;
	temp = home->sectors[i]->walls;
	while (j < home->sectors[i]->nb_of_walls)
	{
		if (temp->top.idx >= 0)
		{
			if (home->nbr_of_sectors == 1)
				return (1);
			if (!(check_valid_connection(&temp->top.p[2], &temp->top.p[0],
						home->sectors[temp->top.idx], i)))
				return (1);
		}
		temp = temp->next;
		j++;
	}
	return (0);
}

static int	check_if_convex(t_sector *sector)
{
	unsigned int	i;
	t_xy			dxy_1;
	t_xy			dxy_2;
	t_wall			*temp;
	int				sign;

	i = 0;
	temp = sector->walls;
	if (sector->nb_of_walls == 3)
		return (1);
	dxy_1 = vec2_dec((t_xy){temp->top.p[2].x, temp->top.p[2].z},
			(t_xy){temp->top.p[0].x, temp->top.p[0].z});
	dxy_2 = vec2_dec((t_xy){temp->next->top.p[2].x, temp->next->top.p[2].z},
			(t_xy){temp->top.p[2].x, temp->top.p[2].z});
	sign = is_negative(vec2_cross(dxy_1, dxy_2));
	while (i < sector->nb_of_walls)
	{
		temp = temp->next;
		dxy_1 = dxy_2;
		dxy_2 = vec2_dec((t_xy){temp->next->top.p[2].x, temp->next->top.p[2].z},
			(t_xy){temp->next->top.p[0].x, temp->next->top.p[0].z});
		if (is_negative(vec2_cross(dxy_1, dxy_2)) != sign)
			return (1);
		i++;
	}
	return (0);
}

int	validate_sectors_data(t_home *home)
{
	unsigned int	i;

	i = 0;
	// if (!(plr_inside(home->sectors[i], &(t_xy){0.0f, 0.0f})))
	// 	map_error_output(6, home);
	while (i < home->nbr_of_sectors)
	{
		if (home->sectors[i]->nb_of_walls < 3)
			map_error_output(7, home);
		if (check_if_sector_has_same_points(home->sectors[i]))
			map_error_output(2, home);
		if (check_if_portals_connected((int)i, home))
			map_error_output(3, home);
		if (check_if_convex(home->sectors[i]))
			map_error_output(4, home);
		// if (check_if_lines_cut(home->sectors[i]))
		// 	map_error_output(5, home);
		i++;
	}
	return (0);
}
