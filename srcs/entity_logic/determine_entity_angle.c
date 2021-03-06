/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_entity_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 14:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 10:36:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	angle_state_logic(float rad, t_entity *entity)
{
	if (rad > -0.3926991 && rad < 0.3926991)
		entity->sprite_state = in_front;
	else if (rad < -0.3926991 && rad > -1.178097)
		entity->sprite_state = front_left;
	else if (rad < -1.178097 && rad > -1.9634954)
		entity->sprite_state = on_left;
	else if (rad < -1.9634954 && rad > -2.7488936)
		entity->sprite_state = back_left;
	else if (rad > 2.7488936 || rad < -2.7488936)
		entity->sprite_state = back;
	else if (rad < 2.7488936 && rad > 1.9634954)
		entity->sprite_state = back_right;
	else if (rad < 1.9634954 && rad > 1.178097)
		entity->sprite_state = on_right;
	else if (rad < 1.178097 && rad > 0.3926991)
		entity->sprite_state = front_right;
	else
		entity->sprite_state = in_front;
}

void	rotate_entity_towards_player(t_entity *entity, t_player *plr)
{
	float	rad;
	t_xy	vec_to_plr;

	vec_to_plr = vec2_unit_vector(vec2_dec(vec3_to_vec2(plr->pos),
				vec3_to_vec2(entity->pos)));
	if (vec_to_plr.x == entity->vec_to_plr_2d.x
		&& vec_to_plr.y == entity->vec_to_plr_2d.y)
		return ;
	rad = vec2_ang(entity->vec_to_plr_2d, vec_to_plr);
	entity->top = rotate_triangle(&entity->top, rad, 'y');
	entity->bot = rotate_triangle(&entity->bot, rad, 'y');
	entity->top.normal = triangle_normal(&entity->top);
	entity->bot.normal = triangle_normal(&entity->bot);
	entity->vec_to_plr_2d = vec_to_plr;
}

void	determine_angle_between_entity_and_plr(t_entity *entity, t_player *plr)
{
	float	rad;
	t_xy	a;
	t_xy	b;

	a = vec2_unit_vector(vec2_dec(vec3_to_vec2(plr->pos),
				vec3_to_vec2(entity->pos)));
	if (a.x == entity->vec_to_plr_2d.x && a.y == entity->vec_to_plr_2d.y)
		return ;
	b = vec3_to_vec2(vec3_dec(vec3_add(entity->pos, entity->dir), entity->pos));
	rad = atan2f(b.y * a.x - b.x * a.y, b.x * a.x + b.y * a.y);
	angle_state_logic(rad, entity);
	rotate_entity_towards_player(entity, plr);
}
