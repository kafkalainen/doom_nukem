/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 10:36:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 19:01:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	show_pickupables(t_entity *pickupable, t_home *home, Uint32 t)
{
	face_entity_towards_player(pickupable);
	entity_gravity(home->sectors[pickupable->sector_idx],
		pickupable, t);
}

static void	show_dead_entity(t_entity *cur_enemy, t_player *plr)
{
	cur_enemy->sprite_state = die_now;
	cur_enemy->sprite_index = 4;
	rotate_entity_towards_player(cur_enemy, plr);
	set_entity_texels_for_frame(cur_enemy);
}

static void	sound_logic(t_entity *enemy, t_player *plr, char sound)
{
	if (sound == 'd')
	{
		if (enemy->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_damage, 40);
		else if (enemy->type == thing)
			play_sound(plr->audio.thing_damage, 30);
	}
	else if (sound == 'x')
	{
		if (enemy->type == skull_skulker)
			play_sound(plr->audio.skull_skulker_death, 40);
		else if (enemy->type == thing)
			play_sound(plr->audio.thing_death, 30);
	}
}

static void	update_entity(t_home *home, t_entity *cur_enemy,
			t_player *plr, Uint32 t)
{
	entity_gravity(home->sectors[cur_enemy->sector_idx], cur_enemy, t);
	if (!cur_enemy->is_aggroed)
		check_aggro(plr, cur_enemy, home);
	if (!cur_enemy->is_aggroed)
		make_noise(cur_enemy, plr, t);
	if (cur_enemy->is_aggroed)
		cur_enemy->dir = cur_enemy->vec_to_plr;
	if (cur_enemy->health <= 0 && die(cur_enemy, t))
		sound_logic(cur_enemy, plr, 'x');
	else if (cur_enemy->health > 0 && !attack_player(home, cur_enemy, plr, t))
		entity_move(cur_enemy, home, t);
	if (take_damage(cur_enemy, t))
		sound_logic(cur_enemy, plr, 'd');
	if (cur_enemy->health > 0)
		determine_angle_between_entity_and_plr(cur_enemy, plr);
	set_entity_texels_for_frame(cur_enemy);
}

void	update_entities(t_home *home, t_player *plr, Uint32 delta_time)
{
	Uint32			i;
	t_entity		*cur_entity;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		cur_entity = home->entity_pool[i];
		cur_entity->vec_to_plr
			= vec3_unit_vector(vec3_dec(plr->pos, cur_entity->pos));
		if (cur_entity->is_pickupable)
			show_pickupables(cur_entity, home, delta_time);
		if (is_enemy(cur_entity->type))
		{
			if (cur_entity->is_active == true)
				update_entity(home, cur_entity, plr, delta_time);
			else
				show_dead_entity(cur_entity, plr);
		}
		i++;
	}
}
