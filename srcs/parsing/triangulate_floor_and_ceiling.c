/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate_floor_and_ceiling.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 08:19:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/08 13:46:49 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_wall	*get_highest_ground(t_sector *sector)
{
	unsigned int	i;
	t_wall			*highest_ground;
	t_wall			*current_ground;

	i = 0;
	current_ground = sector->walls;
	highest_ground = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (current_ground->bottom.p[0].y > highest_ground->bottom.p[0].y)
			highest_ground = current_ground;
		i++;
	}
	return (highest_ground);
}

static t_wall	*get_lowest_ceiling(t_sector *sector)
{
	unsigned int	i;
	t_wall			*lowest_ceiling;
	t_wall			*current_ceiling;

	i = 0;
	lowest_ceiling = sector->walls;
	current_ceiling = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (current_ceiling->top.p[1].y < lowest_ceiling->top.p[1].y)
			lowest_ceiling = current_ceiling;
		i++;
	}
	return (lowest_ceiling);
}

unsigned int	triangulate_floor(t_sector *sector, char choice)
{
	t_wall			*current_wall;
	t_xyz			origin;
	t_surface		*new_surf;
	unsigned int	i;

	i = 0;
	sector->ground = NULL;
	current_wall = get_highest_ground(sector);
	origin = current_wall->bottom.p[0];
	current_wall = current_wall->next;
	while (i < sector->nb_of_walls - 2)
	{
		new_surf = new_surface(current_wall, &origin, sector->tex_floor, choice);
		if (!new_surf)
			return (i);
		add_surface(&sector->ground, new_surf);
		current_wall = current_wall->next;
		i++;
	}
	close_surface_list(&sector->ground);
	return (i);
}

unsigned int	triangulate_ceiling(t_sector *sector, char choice)
{
	t_wall			*current_wall;
	t_xyz			origin;
	t_surface		*new_surf;
	unsigned int	i;

	i = 0;
	sector->ceiling = NULL;
	current_wall = get_lowest_ceiling(sector);
	origin = current_wall->top.p[1];
	current_wall = current_wall->next;
	while (i < sector->nb_of_walls - 2)
	{
		new_surf = new_surface(current_wall, &origin, sector->tex_ceil, choice);
		if (!new_surf)
			return (i);
		add_surface(&sector->ceiling, new_surf);
		current_wall = current_wall->next;
		i++;
	}
	close_surface_list(&sector->ceiling);
	return (i);
}
