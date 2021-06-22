/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_slanted_floors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:18:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 07:49:16 by jnivala          ###   ########.fr       */
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
