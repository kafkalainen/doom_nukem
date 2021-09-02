/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_entity_towards_player.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:42:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/02 12:42:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	face_entity_towards_player(t_entity *entity, t_player *plr)
{
	float	angle;
	t_m4x4	y;
	t_xyz	vec_to_plr;

	vec_to_plr = vec3_unit_vector(vec3_dec(plr->pos, entity->pos));
	angle = vec3_ang_axis(entity->dir, vec_to_plr, 'y');
	y = rotation_matrix_y(angle);
	entity->top.p[0] = multi_vec_matrix(&entity->top.p[0], &y);
	entity->top.p[1] = multi_vec_matrix(&entity->top.p[1], &y);
	entity->top.p[2] = multi_vec_matrix(&entity->top.p[2], &y);
	entity->bot.p[0] = multi_vec_matrix(&entity->bot.p[0], &y);
	entity->bot.p[1] = multi_vec_matrix(&entity->bot.p[1], &y);
	entity->bot.p[2] = multi_vec_matrix(&entity->bot.p[2], &y);
	entity->top.normal = vec_to_plr;
	entity->bot.normal = vec_to_plr;
	entity->dir = vec_to_plr;
}
