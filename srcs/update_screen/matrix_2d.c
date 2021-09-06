/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/08 09:16:54 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// static void	transform_sector_bounding_box(t_sector *sector, float delta_dir)
// {
// 	sector->floor_top_right = vec2_rot(sector->floor_top_right,
// 			delta_dir);
// 	sector->floor_bottom_right = vec2_rot(sector->floor_bottom_right,
// 			delta_dir);
// 	sector->floor_top_left = vec2_rot(sector->floor_top_left,
// 			delta_dir);
// 	sector->floor_bottom_left = vec2_rot(sector->floor_bottom_left,
// 			delta_dir);
// }

// static void	translate_sector_bounding_box(t_sector *sector, t_xy step)
// {
// 	sector->floor_top_right = vec2_dec(sector->floor_top_right, step);
// 	sector->floor_bottom_right = vec2_dec(sector->floor_bottom_right, step);
// 	sector->floor_top_left = vec2_dec(sector->floor_top_left, step);
// 	sector->floor_bottom_left = vec2_dec(sector->floor_bottom_left, step);
// }

// void	transform_world_view(t_home *home, float delta_dir)
// {
// 	t_point			*current_point;
// 	unsigned int	i;
// 	unsigned int	walls;

// 	i = 0;
// 	while (i < home->nbr_of_sectors)
// 	{
// 		walls = home->sectors[i]->nb_of_walls;
// 		current_point = home->sectors[i]->points;
// 		while (walls)
// 		{
// 			current_point->x0 = vec2_rot(current_point->x0, delta_dir);
// 			current_point = current_point->next;
// 			walls--;
// 		}
// 		// transform_sector_bounding_box(home->sectors[i], delta_dir);
// 		i++;
// 	}
// }

// void	translate_world_view(t_home *home, t_xy step)
// {
// 	t_point			*current_point;
// 	unsigned int	i;
// 	unsigned int	walls;

// 	i = 0;
// 	while (i < home->nbr_of_sectors)
// 	{
// 		walls = home->sectors[i]->nb_of_walls;
// 		current_point = home->sectors[i]->points;
// 		while (walls)
// 		{
// 			current_point->x0 = vec2_dec(current_point->x0, step);
// 			current_point = current_point->next;
// 			walls--;
// 		}
// 		// translate_sector_bounding_box(home->sectors[i], step);
// 		i++;
// 	}
// }
