/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_entity_towards_player.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 08:42:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 13:38:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	face_entity_towards_player(t_entity *entity)
{
	float	angle;
	t_m4x4	y;

	angle = vec3_ang_axis(entity->dir, entity->vec_to_plr, 'y');
	y = rotation_matrix_y(angle);
	entity->top.p[0] = multi_vec_matrix(&entity->top.p[0], &y);
	entity->top.p[1] = multi_vec_matrix(&entity->top.p[1], &y);
	entity->top.p[2] = multi_vec_matrix(&entity->top.p[2], &y);
	entity->bot.p[0] = multi_vec_matrix(&entity->bot.p[0], &y);
	entity->bot.p[1] = multi_vec_matrix(&entity->bot.p[1], &y);
	entity->bot.p[2] = multi_vec_matrix(&entity->bot.p[2], &y);
	entity->top.normal = entity->vec_to_plr;
	entity->bot.normal = entity->vec_to_plr;
	entity->dir = entity->vec_to_plr;
}
