/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_entity_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 14:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/18 12:30:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	angle_state_logic(float rad, t_entity *entity)
{
	if (rad > -0.3926991 && rad < 0.3926991)
		entity->sprite_state = in_front;
	else if (rad < -0.3926991 && rad > -1.178097)
		entity->sprite_state = front_right;
	else if (rad < -1.178097 && rad > -1.9634954)
		entity->sprite_state = left;
	else if (rad < -1.9634954 && rad > -2.7488936)
		entity->sprite_state = back_left;
	else if (rad > 2.7488936 || rad < -2.7488936)
		entity->sprite_state = back;
	else if (rad < 2.7488936 && rad > 1.9634954)
		entity->sprite_state = back_right;
	else if (rad < 1.9634954 && rad > 1.178097)
		entity->sprite_state = right;
	else if (rad < 1.178097 && rad > 0.3926991)
		entity->sprite_state = front_left;
	else
		entity->sprite_state = in_front;
}

/*
**	Closer to the player the entity is, more it rotates to clockwise.
**	At some point, all the values evaluate to NaN = Not a Number.
**	Clockwise should be negative, where as counter-clockwise should be positive.
**	If switched to using vectors instead of normalized vectors, we end up
**	with nan whenever player is moving away from the entity.
*/
void	determine_angle_between_entity_and_plr(t_entity *entity, t_player *plr)
{
	float	rad;
	t_xy	a;
	t_xy	b;
	t_xyz	new_vector;

	new_vector = vec3_unit_vector(vec3_dec(plr->pos, entity->pos));
	if (check_if_same_point(new_vector, entity->vec_to_plr))
		return ;
	a = vec3_to_vec2(new_vector);
	b = vec3_to_vec2(vec3_dec(vec3_add(entity->pos, entity->dir), entity->pos));
	rad = atan2f(b.y * a.x - b.x * a.y, b.x * a.x + b.y * a.y);
	angle_state_logic(rad, entity);
	rad = vec3_angle(entity->vec_to_plr, new_vector);
	if (rad != 0)
	{
		entity->top = rotate_triangle(&entity->top, rad, 'y');
		entity->bot = rotate_triangle(&entity->bot, rad, 'y');
		entity->top.normal = triangle_normal(&entity->top);
		entity->bot.normal = triangle_normal(&entity->bot);
		entity->vec_to_plr = new_vector;
		// if (isnanf(entity->top.p[0].x))
		// 	printf("x: %f y: %f z: %f\n", entity->top.normal.x,
		// 	entity->top.normal.y, entity->top.normal.z);
		printf("%f\n", rad);
	}
}
