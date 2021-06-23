/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/23 14:56:05 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_texel	*get_tex(int idx, t_texture	**textures)
{
	int	i;

	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	i = 1;
	while (textures[i])
	{
		if (textures[i]->idx == idx)
			return (&textures[i]->tex);
		i++;
	}
	return (NULL);
}

void	add_floor_and_ceiling(t_raster_queue *transformed, t_sector *sector)
{
	Uint32			j;
	t_surface		*ground;
	t_surface		*ceiling;

	ground = sector->ground;
	ceiling = sector->ceiling;
	j = 0;
	while (j < sector->nb_of_ceil)
	{
		transformed->array[transformed->size] = ceiling->tri;
		transformed->size += 1;
		ceiling = ceiling->next;
		j++;
	}
	j = 0;
	while (j < sector->nb_of_ground)
	{
		transformed->array[transformed->size] = ground->tri;
		transformed->size += 1;
		ground = ground->next;
		j++;
	}
}

void	add_objects(t_raster_queue *transformed, t_home *home, int idx)
{
	Uint32			j;

	j = 0;
	while (j < home->nbr_of_entities)
	{
		if (home->entity_pool[j]->sector_idx == idx)
		{
			transformed->array[transformed->size] = translate_triangle(
				&home->entity_pool[j]->top, home->entity_pool[j]->pos);
			transformed->size += 1;
			transformed->array[transformed->size] = translate_triangle(
				&home->entity_pool[j]->bot, home->entity_pool[j]->pos);
			transformed->size += 1;
		}
		j++;
	}
	// j = 0;
	// while (j < home->nbr_of_projectiles)
	// {
	// 	if (home->projectile_pool[j]->sector_idx == idx)
	// 	{
	// 		transformed->array[transformed->size] = translate_triangle(&home->projectile_pool[j]->top, home->entity_pool[j]->coordinates);
	// 		transformed->size += 1;
	// 		transformed->array[transformed->size] = translate_triangle(&home->projectile_pool[j]->bot, home->entity_pool[j]->coordinates);
	// 		transformed->size += 1;
	// 	}
	// 	j++;
	// }
}

void	scan_fov(t_home *home, t_frame *frame, t_player *plr)
{
	t_frame			new_frame;
	t_triangle		temp_array[800];
	unsigned int	j;

	j = 0;
	frame->transformed->size = 0;
	frame->left.wall = home->sectors[frame->idx]->walls;
	continue_from_last_sector(frame->left.wall, &frame->left, frame);
	while (j < home->sectors[frame->idx]->nb_of_walls * 2
		&& !check_connection(frame->left.wall, frame))
	{
		if (frame->left.wall->top.idx >= 0)
		{
			setup_frame(frame, &new_frame, frame->left.wall->top.idx);
			scan_fov(home, &new_frame, plr);
		}
		else
		{
			temp_array[j++] = frame->left.wall->top;
			temp_array[j++] = frame->left.wall->bottom;
		}
		frame->left.wall = frame->left.wall->next;
	}
	frame->transformed->size = j;
	j = 0;
	while ((int)j < frame->transformed->size)
	{
		frame->transformed->array[j] = temp_array[j];
		j++;
	}
	add_floor_and_ceiling(frame->transformed, home->sectors[frame->idx]);
	add_objects(frame->transformed, home, frame->idx);
	draw_sector(frame, home, plr);
	frame->transformed->size = 0;
	// draw_sector(frame, home, plr);
}
