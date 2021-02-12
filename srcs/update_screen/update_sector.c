/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:11:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/12 12:00:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_point			*new_polygon(t_xy x0, int idx)
{
	t_point		*new;

	new = (t_point*)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0 = x0;
		new->idx = idx;
		new->wall_rad = 0;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

static void		assign_points(t_sector *sector)
{
	t_point		*temp;
	t_point		*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 5);
	coord[4].x = 200.0;
	coord[4].y = 0.0;
	coord[3].x = 100.0;
	coord[3].y = 200.0;
	coord[2].x = -50.0;
	coord[2].y = 200.0;
	coord[1].x = -200.0;
	coord[1].y = 0.0;
	coord[0].x = 0.0;
	coord[0].y = -100.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[4], 1);
	temp = sector->points;
	walls--;
	while (walls)
	{

		new = new_polygon(
		coord[walls - 1],
		-1);
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	temp->next = sector->points;
	free(coord);
}

static void		assign_points1(t_sector *sector)
{
	t_point		*temp;
	t_point		*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 6);
	coord[5].x = 100.0;
	coord[5].y = 200.0;
	coord[4].x = 200.0;
	coord[4].y = 0.0;
	coord[3].x = 300.0;
	coord[3].y = 50.0;
	coord[2].x = 300.0;
	coord[2].y = 200.0;
	coord[1].x = 250.0;
	coord[1].y = 400.0;
	coord[0].x = 100.0;
	coord[0].y = 400.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[5], 0);
	temp = sector->points;
	walls--;
	while (walls)
	{
		if (walls == 3)
		{
			new = new_polygon(
				coord[walls - 1],
				2);
		}
		else
		{
			new = new_polygon(
				coord[walls - 1],
				-1);
		}
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	temp->next = sector->points;
	free(coord);
}

static void		assign_points2(t_sector *sector)
{
	t_point		*temp;
	t_point		*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[3].x = 250.0;
	coord[3].y = 400.0;
	coord[2].x = 300.0;
	coord[2].y = 200.0;
	coord[1].x = 500.0;
	coord[1].y = 500.0;
	coord[0].x = 450.0;
	coord[0].y = 600.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[3], 1);
	temp = sector->points;
	walls--;
	while (walls)
	{
		new = new_polygon(
		coord[walls - 1],
		-1);
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	temp->next = sector->points;
	free(coord);
}

static int		assign_sectors(t_home *home)
{
	int i;

	i = 0;
	home->sectors = (t_sector**)malloc(sizeof(t_sector));
	home->nb_of_sectors = 3;
	while(i < 3)
	{
		home->sectors[i] = (t_sector*)malloc(sizeof(t_sector));
		home->sectors[i]->ceiling = 1.0;
		home->sectors[i]->ground = 0.0;
		home->sectors[i]->idx_sector = i;
		home->sectors[i]->nb_of_walls = 4;
		i++;
	}
	home->sectors[0]->nb_of_walls = 5;
	home->sectors[1]->nb_of_walls = 6;
	home->sectors[2]->nb_of_walls = 4;
	assign_points(home->sectors[0]);
	assign_points1(home->sectors[1]);
	assign_points2(home->sectors[2]);
	return (0);
}

// static void		print_points(t_sector *sector)
// {
// 	int		i;
// 	t_point	*temp;

// 	i = 0;
// 	temp = sector->points;
// 	while (temp)
// 	{
// 		printf("x%d\n", i);
// 		printf("%f\n", temp->x0.x);
// 		printf("%f\n", temp->x0.y);
// 		temp = temp->next;
// 		i++;
// 	}
// }

int				update_sector(t_home *home)
{
	assign_sectors(home);
	//print_points(home->sectors[0]);
	return (0);
}
