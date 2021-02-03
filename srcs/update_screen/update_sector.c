/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:11:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/03 09:09:37 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_point	*new_polygon(t_xy x0, int idx)
{
	t_point		*new;

	new = (t_point*)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0 = x0;
		new->normal = vec2_norm(x0);
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

// static void		create_sector_points(t_sector *sector)
// {
// 	int			walls;
// 	t_point	*temp;
// 	t_point	*new;

// 	walls = sector->nb_of_walls;
// 	while (walls)
// 	{
// 		new = new_polygon(
// 			sector->points[walls - 1].x0,
// 			sector->points[walls - 1].idx
// 		);
// 		temp->next = new;
// 		walls--;
// 	}
// }

static void		assign_points(t_sector *sector)
{
	t_point	*temp;
	t_point	*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[3].x = -100.0;
	coord[3].y = -100.0;
	coord[2].x = 100.0;
	coord[2].y = -100.0;
	coord[1].x = 250.0;
	coord[1].y = 200.0;
	coord[0].x = 40.0;
	coord[0].y = 200.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[walls - 1], -1);
	temp = sector->points;
	walls--;
	while (walls)
	{
		if (walls == 3)
			new = new_polygon(
				coord[walls - 1],
				1);
		else
			new = new_polygon(
			coord[walls - 1],
			-1);
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	free(coord);
}

static void		assign_points1(t_sector *sector)
{
	t_point	*temp;
	t_point	*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[3].x = 200.0;
	coord[3].y = 0.0;
	coord[2].x = 300.0;
	coord[2].y = 0.0;
	coord[1].x = 300.0;
	coord[1].y = 250.0;
	coord[0].x = 250.0;
	coord[0].y = 200.0;
	walls = sector->nb_of_walls;
	sector->points = new_polygon(coord[walls - 1], -1);
	temp = sector->points;
	walls--;
	while (walls)
	{
		if (walls == 1)
			new = new_polygon(
			coord[walls - 1],
				0);
		else
			new = new_polygon(
			coord[walls - 1],
			-1);
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	free(coord);
}

static int		assign_sectors(t_home *home)
{
	int i;

	i = 0;
	home->sectors = (t_sector**)malloc(sizeof(t_sector));
	while(i < 2)
	{
		home->sectors[i] = (t_sector*)malloc(sizeof(t_sector));
		home->sectors[i]->ceiling = 1.0;
		home->sectors[i]->ground = 0.0;
		home->sectors[i]->idx_sector = i;
		home->sectors[i]->nb_of_walls = 4;
		i++;
	}
	assign_points(home->sectors[0]);
	assign_points1(home->sectors[1]);
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
