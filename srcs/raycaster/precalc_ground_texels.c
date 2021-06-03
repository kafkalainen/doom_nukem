// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   precalc_ground_texels.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/05/21 11:44:00 by jnivala           #+#    #+#             */
// /*   Updated: 2021/05/21 13:08:30 by jnivala          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

/*
**	TO REMOVED?
*/

// #include "../../headers/doom_nukem.h"

// static void	calc_offset_using_bounding_box(t_point **head,
// 	unsigned int walls, t_plgn *bounding_box)
// {
// 	t_point *temp;

// 	temp = *head;
// 	while (walls)
// 	{
// 		if (bounding_box->top_right.x - bounding_box->top_left.x != 0.0f)
// 			temp->ground_uv.x = (temp->x0.x - bounding_box->top_left.x)
// 				/ (bounding_box->top_right.x - bounding_box->top_left.x);
// 		else
// 			temp->ground_uv.x = (temp->x0.x - bounding_box->top_left.x);
// 		if (bounding_box->bottom_right.y - bounding_box->top_left.y != 0.0f)
// 			temp->ground_uv.y = (temp->x0.y - bounding_box->top_left.y)
// 				/ (bounding_box->bottom_right.y - bounding_box->top_left.y);
// 		else
// 			temp->ground_uv.y = (temp->x0.y - bounding_box->top_left.y);
// 		temp = temp->next;
// 		walls--;
// 	}
// }

// void	precalc_ground_texels(t_home *home)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < home->nbr_of_sectors)
// 	{
// 		calc_offset_using_bounding_box(&home->sectors[i]->points,
// 			home->sectors[i]->nb_of_walls, &home->sectors[i]->bounding_box);
// 		i++;
// 	}
// }
