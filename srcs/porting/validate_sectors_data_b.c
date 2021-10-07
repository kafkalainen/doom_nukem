/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sectors_data_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 19:09:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 11:20:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	triangle_same_triangles(t_wall *test, t_wall *temp,
	unsigned int i, unsigned int j)
{
	if (test->top.p[0].x == temp->top.p[0].x
		&& test->top.p[0].y == temp->top.p[0].y
		&& test->top.p[0].z == temp->top.p[0].z
		&& i != j)
		return (1);
	else if (test->bot.p[2].x == temp->bot.p[2].x
		&& test->bot.p[2].y == temp->bot.p[2].y
		&& test->bot.p[2].z == temp->bot.p[2].z
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
				|| triangle_same_points_test(&test->bot))
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
