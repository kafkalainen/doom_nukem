/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 08:40:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/05 15:35:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	vec3_angle(t_xyz a, t_xyz b)
{
	float	dot;
	float	mag_a;
	float	mag_b;

	mag_a = vec3_eucl_dist(a);
	mag_b = vec3_eucl_dist(b);
    dot = vec3_dot_product(a, b) / (mag_a * mag_b);
	return (acosf(dot));
}

void	translate_entity(t_triangle *tri1, t_triangle *tri2,
				t_entity *entity)
{
	*tri1 = translate_triangle(&entity->top, entity->pos);
	*tri2 = translate_triangle(&entity->bot, entity->pos);
}
