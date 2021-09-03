/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_look.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:17:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 16:52:01 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	check_if_entities(t_home *home, t_player *plr,
		t_bool *visible_object)
{
	Uint32		i;
	t_xyz		isection;
	t_triangle	tested[2];

	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == plr->cur_sector
			&& check_if_entity_is_active(home->entity_pool[i]))
		{
			translate_entity(&tested[0], &tested[1], home->entity_pool[i]);
			if (vec3_ray_triangle_intersect(&tested[0],
					plr->pos, plr->look_dir, &isection)
				|| vec3_ray_triangle_intersect(&tested[1],
					plr->pos, plr->look_dir, &isection))
				*visible_object = 1;
			if (*visible_object && get_distance_squared(isection, plr->pos)
				< 6.25f)
			{
				plr->display_object = home->entity_pool[i]->type;
				break ;
			}
		}
		i++;
	}
}

static void	check_if_doors(t_home *home, t_player *plr, t_bool *visible_object)
{
	Uint32		i;
	t_xyz		isection;
	t_wall		*wall;

	i = 0;
	wall = home->sectors[plr->cur_sector]->walls;
	while (i < home->sectors[plr->cur_sector]->nb_of_walls)
	{
		if (wall->is_door)
		{
			if (vec3_ray_triangle_intersect(&wall->top,
					plr->pos, plr->look_dir, &isection)
				|| vec3_ray_triangle_intersect(&wall->bottom,
					plr->pos, plr->look_dir, &isection))
				*visible_object = 1;
			if (*visible_object && get_distance_squared(isection, plr->pos)
				< 3.25f)
			{
				plr->display_object = wall->is_locked;
				break ;
			}
		}
		wall = wall->next;
		i++;
	}
}

t_bool	player_look(t_home *home, t_player *plr)
{
	t_bool		visible_entity;
	t_bool		visible_door;

	visible_door = false;
	visible_entity = false;
	check_if_doors(home, plr, &visible_door);
	check_if_entities(home, plr, &visible_entity);
	if (!visible_door && !visible_entity)
		plr->display_object = 0;
	return (true);
}
