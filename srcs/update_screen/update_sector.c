/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:11:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/20 14:37:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_polygon	*new_polygon(t_xy x0, int idx)
{
	t_polygon		*new;

	new = (t_polygon*)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0 = x0;
		new->normal = vec2_norm(x0);
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

// static void		create_sector_polygons(t_sector *sector)
// {
// 	int			walls;
// 	t_polygon	*temp;
// 	t_polygon	*new;

// 	walls = sector->nb_of_walls;
// 	while (walls)
// 	{
// 		new = new_polygon(
// 			sector->polygons[walls - 1].x0,
// 			sector->polygons[walls - 1].idx
// 		);
// 		temp->next = new;
// 		walls--;
// 	}
// }

static void		assign_polygons(t_sector *sector)
{
	t_polygon	*temp;
	t_polygon	*new;
	t_xy		*coord;
	int			walls;

	coord = (t_xy*)malloc(sizeof(t_xy) * 4);
	coord[0].x = 0.0;
	coord[0].y = 0.0;
	coord[1].x = 5.0;
	coord[1].y = 0.0;
	coord[2].x = 5.0;
	coord[2].y = 5.0;
	coord[3].x = 0.0;
	coord[3].y = 5.0;
	walls = sector->nb_of_walls;
	sector->polygons = new_polygon(coord[walls - 1], 1);
	temp = sector->polygons;
	while (walls)
	{
		new = new_polygon(
			coord[walls - 1],
			1
		);
		temp->next = new;
		temp = temp->next;
		walls--;
	}
	free(coord);
}

static int		assign_sectors(t_home *home)
{
	home->sectors = (t_sector**)malloc(sizeof(t_sector));
	home->sectors[0] = (t_sector*)malloc(sizeof(t_sector));
	home->sectors[0]->ceiling = 1.0;
	home->sectors[0]->ground = 0.0;
	home->sectors[0]->idx_sector = 0;
	home->sectors[0]->nb_of_walls = 4;
	assign_polygons(home->sectors[0]);
	return (0);
}

static void		print_polygons(t_sector *sector)
{
	int		i;
	t_polygon	*temp;

	i = 0;
	temp = sector->polygons;
	while (temp)
	{
		printf("x%d\n", i);
		printf("%f\n", temp->x0.x);
		printf("%f\n", temp->x0.y);
		temp = temp->next;
		i++;
	}
}

int				update_sector(t_home *home)
{
	assign_sectors(home);
	print_polygons(home->sectors[0]);
	return (0);
}
