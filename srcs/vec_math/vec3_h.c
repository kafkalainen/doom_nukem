/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 08:40:24 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/11 13:24:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	vec3_angle(t_xyz to_be_turned, t_xyz compared)
{
	float	dot;
	float	mag_a;
	float	mag_b;
	float	sign;

	mag_a = vec3_eucl_dist(to_be_turned);
	mag_b = vec3_eucl_dist(compared);
	dot = vec3_dot_product(to_be_turned, compared);
	dot /= mag_a * mag_b;
	if (dot < -1.0)
		dot = -1.0f;
	else if (dot > 1.0)
		dot = 1.0f;
	sign = -to_be_turned.z * compared.x + to_be_turned.x * compared.z;
	if (sign < 0)
		sign = -1.0f;
	else if (sign > 0)
		sign = 1.0f;
	else
		return (0.0f);
	return (sign * acosf(dot));
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

float	vec3_ang_axis(t_xyz to_be_turned, t_xyz compared, char axis)
{
	float	rotation;
	float	angle;
	t_xy	v[2];

	if (axis == 'x')
	{
		v[0] = vec2(to_be_turned.z, to_be_turned.y);
		v[1] = vec2(compared.z, compared.y);
	}
	else if (axis == 'y')
	{
		v[0] = vec2(to_be_turned.x, to_be_turned.z);
		v[1] = vec2(compared.x, compared.z);
	}
	else if (axis == 'z')
	{
		v[0] = vec2(-to_be_turned.x, to_be_turned.y);
		v[1] = vec2(-compared.x, compared.y);
	}
	rotation = vec2_determine_rotation(v[0], v[1], axis);
	if (rotation == 0.0f || rotation == PI)
		return (rotation);
	rotation = ft_signf(rotation);
	angle = set_valid(vec2_dot(v[0], v[1]) / (vec2_mag(v[0]) * vec2_mag(v[1])));
	return (rotation * acosf(angle));
}
