/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_unit_normals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:20:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/03 17:34:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	calc_wall_normals(t_sector *sector)
{
	Uint32		i;
	t_wall		*walls;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		walls->top.normal = triangle_normal(&walls->top);
		walls->bot.normal = triangle_normal(&walls->bot);
		walls->top.hull = true;
		walls->bot.hull = true;
		walls = walls->next;
		i++;
	}
}

static void	calc_ceil_ground_normals(t_sector *sector)
{
	Uint32		i;
	t_surface	*ceil_ground;

	i = 0;
	ceil_ground = sector->ceiling;
	while (i < sector->nb_of_ceil)
	{
		ceil_ground->tri.normal = triangle_normal(&ceil_ground->tri);
		ceil_ground->tri.hull = true;
		ceil_ground = ceil_ground->next;
		i++;
	}
	i = 0;
	ceil_ground = sector->ground;
	while (i < sector->nb_of_ground)
	{
		ceil_ground->tri.normal = triangle_normal(&ceil_ground->tri);
		ceil_ground->tri.hull = true;
		ceil_ground = ceil_ground->next;
		i++;
	}
}

static t_bool	check_if_inner_wall(t_wall *test, t_home *home)
{
	t_uint	i;
	t_uint	j;
	t_wall	*tmp;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		tmp = home->sectors[i]->walls;
		while (j++ < home->sectors[i]->nb_of_walls)
		{
			if (check_if_hull(test) && check_if_hull(tmp))
			{
				if (vec2_check_if_same_point(test->point, tmp->next->point)
					&& vec2_check_if_same_point(test->next->point, tmp->point))
					return (true);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (false);
}

static void	add_non_hull_portals(t_sector *sector, t_home *home)
{
	t_uint	i;
	t_wall	*walls;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (walls->is_door || walls->is_window)
		{
			walls->next->top.hull = false;
			walls->next->bot.hull = false;
		}
		if (check_if_inner_wall(walls, home))
		{
			walls->top.hull = false;
			walls->bot.hull = false;
		}
		walls = walls->next;
		i++;
	}
}

void	calc_unit_normals(t_home *home)
{
	Uint32			i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		calc_wall_normals(home->sectors[i]);
		calc_ceil_ground_normals(home->sectors[i]);
		add_non_hull_portals(home->sectors[i], home);
		i++;
	}
}
