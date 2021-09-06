/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_offsets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:11:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/29 15:17:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uvz	calculate_texel_offset(t_uvz from, t_uvz to, float t)
{
	t_uvz	sum;

	sum.u = t * (to.u - from.u) + from.u;
	sum.v = t * (to.v - from.v) + from.v;
	sum.w = t * (to.w - from.w) + from.w;
	return (sum);
}

float	calculate_lumel_offset(float from, float to, float t)
{
	float	sum;

	sum = t * (to - from) + from;
	return (sum);
}
