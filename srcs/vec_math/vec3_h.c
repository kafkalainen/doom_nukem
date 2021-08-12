/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 08:40:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/12 15:10:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	vec3_angle(t_xyz a, t_xyz b)
{
	float	dot;
	float	dot_ccw;
	float	mag_a;
	float	mag_b;

	mag_a = vec3_eucl_dist(a);
	mag_b = vec3_eucl_dist(b);
	dot = vec3_dot_product(a, b);
	dot_ccw = a.x * -b.z + a.z * b.x;
	if (dot_ccw > 0)
		return (-acosf(dot / (mag_a * mag_b)));
	else if (dot_ccw < 0)
		return (acosf(dot / (mag_a * mag_b)));
	else
		return (0.0f);
}

void	translate_entity(t_triangle *tri1, t_triangle *tri2,
				t_entity *entity)
{
	*tri1 = translate_triangle(&entity->top, entity->pos);
	*tri2 = translate_triangle(&entity->bot, entity->pos);
}

void	set_entity_texels_for_frame(t_entity *entity)
{
	Uint32	x;
	Uint32	y;

	x = entity->sprite_state;
	y = entity->anim_offset;
	if (x > 9 || y > 5)
		return ;
	entity->top.uv[0] = (t_uvz){x * 0.1f, (y + 1) * 0.166666667f, 1.0f};
	entity->top.uv[1] = (t_uvz){x * 0.1f, y * 0.166666667f, 1.0f};
	entity->top.uv[2] = (t_uvz){(x + 1) * 0.1f, y * 0.166666667f, 1.0f};
	entity->bot.uv[0] = (t_uvz){x * 0.1f, (y + 1) * 0.166666667f, 1.0f};
	entity->bot.uv[1] = (t_uvz){(x + 1) * 0.1f, y * 0.166666667f, 1.0f};
	entity->bot.uv[2] = (t_uvz){(x + 1) * 0.1f, (y + 1) * 0.166666667f, 1.0f};
}

void	initialize_lumels(float *p0, float *p1, float *p2, float init)
{
	*p0 = init;
	*p1 = init;
	*p2 = init;
}
