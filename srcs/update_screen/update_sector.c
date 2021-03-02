/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:11:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/02 09:46:51 by jnivala          ###   ########.fr       */
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

	coord = (t_xy*)malloc(sizeof(t_xy) * 6);
	coord[5].x = 30.0;
	coord[5].y = 100.0;
	coord[4].x = -30.0;
	coord[4].y = 100.0;
	coord[3].x = -100.0;
	coord[3].y = 100.0;
	coord[2].x = -100.0;
	coord[2].y = -100.0;
	coord[1].x = 100.0;
	coord[1].y = -100.0;
	coord[0].x = 100.0;
	coord[0].y = 100.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[5], 1);
	temp = sector->points;
	walls--;
	while (walls)
	{
		new = new_polygon(
			coord[walls - 1],
			-4);
		if (walls == 1)
			new->c = 'b';
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

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[3].x = -30.0;
	coord[3].y = 100.0;
	coord[2].x = 30.0;
	coord[2].y = 100.0;
	coord[1].x = 30.0;
	coord[1].y = 150.0;
	coord[0].x = -30.0;
	coord[0].y = 150.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[3], 0);
	temp = sector->points;
	walls--;
	while (walls)
	{
		if (walls == 2)
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

	coord = (t_xy*)malloc(sizeof(t_xy) * 8);
	coord[7].x = -30.0;
	coord[7].y = 150.0;
	coord[6].x = 30.0;
	coord[6].y = 150.0;
	coord[5].x = 100.0;
	coord[5].y = 150.0;
	coord[4].x = 100.0;
	coord[4].y = 250.0;
	coord[3].x = 20.0;
	coord[3].y = 250.0;
	coord[2].x = -20.0;
	coord[2].y = 250.0;
	coord[1].x = -100.0;
	coord[1].y = 250.0;
	coord[0].x = -100.0;
	coord[0].y = 150.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[7], 1);
	temp = sector->points;
	walls--;
	while (walls)
	{
		if (walls == 4)
		{
			new = new_polygon(
				coord[walls - 1],
				3);
		}
		else
		{
			new = new_polygon(
				coord[walls - 1],
				-2);
		}
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	temp->next = sector->points;
	free(coord);
}

static void		assign_points3(t_sector *sector)
{
	t_point		*temp;
	t_point		*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[3].x = -20.0;
	coord[3].y = 250.0;
	coord[2].x = 20.0;
	coord[2].y = 250.0;
	coord[1].x = 20.0;
	coord[1].y = 350.0;
	coord[0].x = -20.0;
	coord[0].y = 350.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[3], 2);
	temp = sector->points;
	walls--;
	while (walls)
	{
		new = new_polygon(
			coord[walls - 1],
		-3);
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
	home->nb_of_sectors = 4;
	while(i < 4)
	{
		home->sectors[i] = (t_sector*)malloc(sizeof(t_sector));
		home->sectors[i]->ceiling = 1.0;
		home->sectors[i]->ground = 0.0;
		home->sectors[i]->idx_sector = i;
		home->sectors[i]->nb_of_walls = 4;
		i++;
	}
	home->sectors[0]->nb_of_walls = 6;
	home->sectors[1]->nb_of_walls = 4;
	home->sectors[2]->nb_of_walls = 8;
	home->sectors[3]->nb_of_walls = 4;
	assign_points(home->sectors[0]);
	assign_points1(home->sectors[1]);
	assign_points2(home->sectors[2]);
	assign_points3(home->sectors[3]);
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
