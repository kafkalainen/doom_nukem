/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate_floor_and_ceiling.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 08:19:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/02 17:04:06 by jnivala          ###   ########.fr       */
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

unsigned int	triangulate_floor_and_ceiling(t_sector *sector)
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
	new_surf = new_surface(current_wall, &origin, sector->tex_floor);
	if (new_surf)
		add_surface(&sector->ground, new_surf);
	else
		return (1);
	if (sector->nb_of_walls == 3)
		return (0);
	current_wall = current_wall->next;
	while (i < sector->nb_of_walls - 3)
	{
		new_surf = new_surface(current_wall, &origin, sector->tex_floor);
		if (new_surf)
			add_surface(&sector->ground, new_surf);
		else
			return (i + 2);
		current_wall = current_wall->next;
		i++;
	}
	close_surface_list(&sector->ground);
	return (i);
}
