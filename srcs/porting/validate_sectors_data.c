/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sectors_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:06:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/05 12:53:54 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	check_if_sector_has_same_points(t_sector *sector)
{
	unsigned int	i;
	unsigned int	j;
	t_xy			coord;
	t_point			*temp;
	t_point			*test;

	i = 0;
	temp = sector->points;
	while (i < sector->nb_of_walls)
	{
		coord = temp->x0;
		j = 0;
		test = sector->points;
		while (j < sector->nb_of_walls)
		{
			if (test->x0.x == coord.x && test->x0.y == coord.y
				&& i != j)
				return (1);
			test = test->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

static int	check_valid_connection(t_xy *p0, t_xy *p1, t_sector *sector, int i)
{
	unsigned int	j;
	t_point			*temp;

	j = 0;
	temp = sector->points;
	while (j < sector->nb_of_walls)
	{
		if (temp->idx == i)
		{
			if (temp->x0.x == p0->x
				&& temp->x0.y == p0->y
				&& temp->next->x0.x == p1->x
				&& temp->next->x0.y == p1->y)
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
	t_point			*temp;

	j = 0;
	temp = home->sectors[i]->points;
	while (j < home->sectors[i]->nb_of_walls)
	{
		if (temp->idx >= 0)
		{
			if (home->nbr_of_sectors == 1)
				return (1);
			if (!(check_valid_connection(&temp->next->x0, &temp->x0,
						home->sectors[temp->idx], i)))
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
	t_point			*temp;
	float			z;

	i = 0;
	temp = sector->points;
	while (i < sector->nb_of_walls)
	{
		dxy_1 = vec2_dec(temp->next->x0, temp->x0);
		dxy_2 = vec2_dec(temp->next->next->x0, temp->next->x0);
		if (i == 0)
			z = vec2_cross(dxy_1, dxy_2);
		else
		{
			if (!(vec2_cross(dxy_1, dxy_2) < 0 && z < 0)
				|| !(vec2_cross(dxy_1, dxy_2) > 0 && z > 0))
				return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

int	validate_sectors_data(t_home *home)
{
	unsigned int	i;

	i = 0;
	if (!(plr_inside(home->sectors[i], &(t_xy){0.0f, 0.0f})))
		map_error_output(6, home);
	while (i < home->nbr_of_sectors)
	{
		if (home->sectors[i]->nb_of_walls < 3)
			map_error_output(4, home);
		if (check_if_sector_has_same_points(home->sectors[i]))
			map_error_output(2, home);
		if (check_if_portals_connected((int)i, home))
			map_error_output(3, home);
		if (check_if_convex(home->sectors[i]))
			map_error_output(4, home);
		if (check_if_lines_cut(home->sectors[i]))
			map_error_output(5, home);
		i++;
	}
	return (0);
}
