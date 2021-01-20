/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 10:11:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/20 13:10:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
#include "../../dn_map.h"

t_polygon	*new_polygon(t_xy x0, int idx, int conn)
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

static void		create_sector_polygons(t_sector *sector)
{
	int			walls;
	t_polygon	*temp;

	walls = 5;
	while (walls)
	{
		temp = new_polygon(x0, idx, conn);
		temp->next = new;
		walls--;
	}
}

static void		assign_polygons(t_polygon *sector)
{
	t_xy		x0;
	t_xy		x1;
	t_xy		x2;
	t_xy		x3;
	t_xy		x4;

	x0.x = 0.0;
	x0.y = 0.0;
	x1.x = 5.0;
	x1.y = 2.0;
	x2.x = 7.0;
	x2.y = 9.0;
	x3.x = 2.0;
	x3.y = 9.0;
	x4.x = 0.0;
	x4.y = 1.0;

}

static int		assign_sectors(t_home *home)
{
	home->sectors = (t_sector*)malloc(sizeof(t_sector) * 2);
	home->sectors[0].ceiling = 1.0;
	home->sectors[0].ground = 0.0;
	home->sectors[0].idx_sector = 0;
	home->sectors[0].nb_of_walls = 5;
	assign_polygons(&home->sectors[0].polygons);
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
	print_polygons(&home->sectors[0]);
	return (0);
}
