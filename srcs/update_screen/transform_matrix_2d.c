/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix_2d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:10:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/19 14:14:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			transform_world_view(t_home *home, float delta_dir)
{
	t_point		*current_point;
	int			i;
	int			walls;

	i = 0;
	while (i < home->nb_of_sectors)
	{
		walls = home->sectors[i]->nb_of_walls;
		current_point = home->sectors[i]->points;
		while (walls)
		{
			current_point->x0 = vec2_rot(current_point->x0, delta_dir);
			current_point = current_point->next;
			walls--;
		}
		i++;
	}
}


void			translate_world_view(t_home *home, t_xy step)
{
	t_point		*current_point;
	int			i;
	int			walls;

	i = 0;
	while (i < home->nb_of_sectors)
	{
		walls = home->sectors[i]->nb_of_walls;
		current_point = home->sectors[i]->points;
		while (walls)
		{
			current_point->x0 = vec2_dec(current_point->x0, step);
			current_point = current_point->next;
			walls--;
		}
		i++;
	}
}

// void			trans_world_view(t_home *home, t_xy step, float delta_dir)
// {
// 	t_point		*current_point;
// 	t_point		*orig_point;
// 	int			i;
// 	int			walls;
// 	static t_xy	prev_step;

// 	i = 0;
// 	while (i < home->nb_of_sectors)
// 	{
// 		walls = home->sectors[i]->nb_of_walls;
// 		current_point = home->sectors[i]->points;
// 		orig_point = home->orig_sectors[i]->points;
// 		while (walls)
// 		{
// 			current_point->x0 = vec2_rot(orig_point->x0, delta_dir);
// 			if (prev_step.x != step.x && prev_step.y != step.y)
// 			{
// 				current_point->x0 = vec2_dec(current_point->x0, step);
// 			current_point = current_point->next;
// 			orig_point = orig_point->next;
// 			walls--;
// 		}
// 		i++;
// 	}
// }
