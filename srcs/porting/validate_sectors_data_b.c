/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sectors_data_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:09:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 08:35:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// int	check_if_lines_cut(t_sector *sector)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	t_wall			*temp;
// 	t_wall			*test;
// 	t_xy			next;
// 	t_xy			one_after;

// 	if (sector->nb_of_walls < 4)
// 		return (0);
// 	j = 0;
// 	temp = sector->walls;
// 	while (j < sector->nb_of_walls)
// 	{
// 		i = 0;
// 		test = temp->next;
// 		while (i < sector->nb_of_walls - 2)
// 		{
// 			next = vec2(test->top.p[0].x, test->top.p[0].z);
// 			one_after = vec2(test->top.p[2].x, test->top.p[2].z);
// 			if (check_if_lseg_intersects(temp, &next,
//					&one_after) && temp != test)
// 			{
// 				if (temp->top.p[2].x != test->top.p[2].x
// 					&& temp->top.p[2].y != test->top.p[2].y)
// 					return (1);
// 			}
// 			test = test->next;
// 			i++;
// 		}
// 		temp = temp->next;
// 		j++;
// 	}
// 	return (0);
// }

static int	triangle_same_triangles(t_wall *test, t_wall *temp,
	unsigned int i, unsigned int j)
{
	if (test->top.p[0].x == temp->top.p[0].x
		&& test->top.p[0].y == temp->top.p[0].y
		&& test->top.p[0].z == temp->top.p[0].z
		&& i != j)
		return (1);
	else if (test->bottom.p[2].x == temp->bottom.p[2].x
		&& test->bottom.p[2].y == temp->bottom.p[2].y
		&& test->bottom.p[2].z == temp->bottom.p[2].z
		&& i != j)
		return (1);
	else
		return (0);
}

static int	triangle_same_points_test(t_triangle *test)
{
	if (test->p[0].x == test->p[1].x && test->p[0].y == test->p[1].y
		&& test->p[0].z == test->p[1].z)
		return (1);
	else if (test->p[0].x == test->p[2].x && test->p[0].y == test->p[2].y
		&& test->p[0].z == test->p[2].z)
		return (1);
	else
		return (0);
}

int	check_if_sector_has_same_points(t_sector *sector)
{
	unsigned int	i;
	unsigned int	j;
	t_wall			*temp;
	t_wall			*test;

	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		j = 0;
		test = sector->walls;
		while (j < sector->nb_of_walls)
		{
			if (triangle_same_points_test(&test->top)
				|| triangle_same_points_test(&test->bottom))
				return (1);
			if (triangle_same_triangles(test, temp, i, j))
				return (1);
			test = test->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
	return (0);
}
