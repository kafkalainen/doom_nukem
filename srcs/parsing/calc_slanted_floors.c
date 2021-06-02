/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_slanted_floors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:18:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/02 15:29:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


/*
**	ERRORS
*/
// static t_point	*get_highest_ground(t_sector *sector)
// {
// 	unsigned int	same_height;
// 	unsigned int	i;
// 	t_point			*highest_ground;
// 	t_point			*current_ground;

// 	i = 0;
// 	same_height = 0;
// 	current_ground = sector->points;
// 	highest_ground = sector->points;
// 	while (i < sector->nb_of_walls)
// 	{
// 		if (highest_ground->height.ground < current_ground->height.ground)
// 			highest_ground = current_ground;
// 		if (highest_ground->height.ground == current_ground->height.ground)
// 			same_height++;
// 		current_ground = current_ground->next;
// 		i++;
// 	}
// 	if (same_height == sector->nb_of_walls)
// 		return (NULL);
// 	else
// 		return (highest_ground);
// }

// static t_point	*get_lowest_ceiling(t_sector *sector)
// {
// 	unsigned int	same_height;
// 	unsigned int	i;
// 	t_point			*lowest_ceiling;
// 	t_point			*current_ceiling;

// 	i = 0;
// 	same_height = 0;
// 	current_ceiling = sector->points;
// 	lowest_ceiling = sector->points;
// 	while (i < sector->nb_of_walls)
// 	{
// 		if (lowest_ceiling->height.ceiling > current_ceiling->height.ceiling)
// 			lowest_ceiling = current_ceiling;
// 		if (lowest_ceiling->height.ceiling == current_ceiling->height.ceiling)
// 			same_height++;
// 		current_ceiling = current_ceiling->next;
// 		i++;
// 	}
// 	if (same_height == sector->nb_of_walls)
// 		return (NULL);
// 	else
// 		return (lowest_ceiling);
// }

// static void	linearly_interpolate_ground(t_sector *sector, t_point *ground)
// {
// 	t_point			*opposing_ground;
// 	t_point			*cur_ground;
// 	float			ground_angle;
// 	float			height_diff;

// 	cur_ground = ground->next;
// 	opposing_ground = get_opposing_wall(ground, sector->nb_of_walls);
// 	height_diff = ground->height.ground - opposing_ground->height.ground;
// 	ground_angle = atan2f(height_diff,
// 			vec2_distance_from_point_to_line(&opposing_ground->x0,
// 				&opposing_ground->next->x0, &ground->x0));
// 	while (cur_ground != ground)
// 	{
// 		if (height_diff != 0)
// 			cur_ground->height.ground = opposing_ground->height.ground
// 				+ tanf(ground_angle) * vec2_distance_from_point_to_line(
// 					&opposing_ground->x0,
// 					&opposing_ground->next->x0, &cur_ground->x0);
// 		cur_ground = cur_ground->next;
// 	}
// }

// static void	linearly_interpolate_ceiling(t_sector *sector, t_point *ceiling)
// {
// 	t_point			*opposing_ceiling;
// 	t_point			*cur_ceiling;
// 	float			ground_angle;
// 	float			height_diff;

// 	cur_ceiling = ceiling->next;
// 	opposing_ceiling = get_opposing_wall(ceiling, sector->nb_of_walls);
// 	height_diff = ceiling->height.ceiling - opposing_ceiling->height.ceiling;
// 	ground_angle = atan2f(height_diff,
// 			vec2_distance_from_point_to_line(&opposing_ceiling->x0,
// 				&opposing_ceiling->next->x0, &ceiling->x0));
// 	while (cur_ceiling != ceiling)
// 	{
// 		cur_ceiling->height.ceiling = opposing_ceiling->height.ceiling
// 			+ tanf(ground_angle) * vec2_distance_from_point_to_line(
// 				&opposing_ceiling->x0, &opposing_ceiling->next->x0,
// 				&cur_ceiling->x0);
// 		cur_ceiling = cur_ceiling->next;
// 	}
// }

// void	calc_slanted_floors(t_home *home)
// {
// 	unsigned int	i;
// 	t_point			*lowest_ceiling;
// 	t_point			*highest_ground;

// 	i = 0;
// 	while (i < home->nbr_of_sectors)
// 	{
// 		lowest_ceiling = get_lowest_ceiling(home->sectors[i]);
// 		highest_ground = get_highest_ground(home->sectors[i]);
// 		if (highest_ground)
// 			linearly_interpolate_ground(home->sectors[i], highest_ground);
// 		if (lowest_ceiling)
// 			linearly_interpolate_ceiling(home->sectors[i], lowest_ceiling);
// 		i++;
// 	}
// }
