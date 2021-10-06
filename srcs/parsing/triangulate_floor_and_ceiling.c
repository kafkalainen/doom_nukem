/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate_floor_and_ceiling.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 08:19:32 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 17:14:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void		move_towards_centroid(t_surface *surface, t_sector *sector)
// {
// 	t_xyz	unit_normal[3];

// 	unit_normal[0] = vec3_unit_vector(vec3_dec(
// 		vec3(sector->centroid.x, surface->tri.p[0].y, sector->centroid.y),
// 		surface->tri.p[0]));
// 	unit_normal[1] = vec3_unit_vector(vec3_dec(
// 		vec3(sector->centroid.x, surface->tri.p[1].y, sector->centroid.y),
// 		surface->tri.p[1]));
// 	unit_normal[2] = vec3_unit_vector(vec3_dec(
// 		vec3(sector->centroid.x, surface->tri.p[2].y, sector->centroid.y),
// 		surface->tri.p[2]));
// 	surface->tri.p[0]
// 		= translate_point(&surface->tri.p[0], vec3_mul(unit_normal[0], 0.005f));
// 	surface->tri.p[1]
// 		= translate_point(&surface->tri.p[1], vec3_mul(unit_normal[1], 0.005f));
// 	surface->tri.p[2]
// 		= translate_point(&surface->tri.p[2], vec3_mul(unit_normal[2], 0.005f));
// }

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
		if (current_ground->bot.p[0].y > highest_ground->bot.p[0].y)
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
	origin = current_wall->bot.p[0];
	current_wall = current_wall->next;
	while (i < sector->nb_of_walls - 2)
	{
		new_surf = new_surface(current_wall, &origin,
				sector->tex_floor, choice);
		if (!new_surf)
			return (i);
		map_texel(new_surf, sector);
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
		map_texel(new_surf, sector);
		add_surface(&sector->ceiling, new_surf);
		current_wall = current_wall->next;
		i++;
	}
	close_surface_list(&sector->ceiling);
	return (i);
}
