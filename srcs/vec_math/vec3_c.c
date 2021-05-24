/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:04:51 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/24 15:18:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uvz	uvz_calculate_value_with_delta(float delta_x, t_uvz delta_u, t_uvz delta_v)
{
	t_uvz	value;

	value.z = delta_x * delta_u.z + delta_v.z;
	value.u = delta_x * delta_u.u + delta_v.u;
	value.v = delta_x * delta_u.v + delta_v.v;
	return (value);
}
