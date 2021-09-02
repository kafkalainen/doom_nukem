/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:36:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 10:34:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	show_dead_entity(t_entity *cur_enemy, t_player *plr)
{
	cur_enemy->state = die_now;
	cur_enemy->sprite_index = 4;
	rotate_entity_towards_player(cur_enemy, plr);
	set_entity_texels_for_frame(cur_enemy);
}

static void	update_entity(t_home *home, t_entity *cur_enemy,
			t_player *plr, Uint32 t)
{
	entity_gravity(home->sectors[cur_enemy->sector_idx], cur_enemy, t);
	check_aggro(plr, cur_enemy,
		home->sectors[cur_enemy->sector_idx]);
	if (cur_enemy->is_aggroed)
		cur_enemy->dir = vec3_unit_vector(vec3_dec(plr->pos,
					cur_enemy->pos));
	if (!attack_player(home, cur_enemy, plr, t))
		entity_move(cur_enemy, home, t);
	take_damage(cur_enemy, t);
	determine_angle_between_entity_and_plr(cur_enemy, plr);
	if (cur_enemy->health <= 0)
		die(cur_enemy, t);
	set_entity_texels_for_frame(cur_enemy);
}

void	update_enemies(t_home *home, t_player *plr, Uint32 delta_time)
{
	Uint32			i;
	t_entity		*cur_enemy;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		cur_enemy = home->entity_pool[i];
		if (cur_enemy->is_pickupable)
		{
			face_entity_towards_player(cur_enemy, plr);
			entity_gravity(home->sectors[cur_enemy->sector_idx],
				cur_enemy, delta_time);
		}
		if (cur_enemy->is_active != false)
		{
			if (cur_enemy->entity_type == skull_skulker
				|| cur_enemy->entity_type == thing)
				update_entity(home, cur_enemy, plr, delta_time);
		}
		else
		{
			if (cur_enemy->entity_type == skull_skulker
				|| cur_enemy->entity_type == thing)
				show_dead_entity(cur_enemy, plr);
		}
		i++;
	}
}
