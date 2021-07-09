/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:39:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/09 11:41:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_texel(t_uvz *texel, t_uvz *start, float offset,
					t_uvz *end)
{
	texel->u = (1.0f - offset) * start->u + offset * end->u;
	texel->v = (1.0f - offset) * start->v + offset * end->v;
	texel->w = (1.0f - offset) * start->w + offset * end->w;
}

void	calc_lumel(float *lumel, float *start, float offset, float *end)
{
	*lumel = (1.0f - offset) * *start + offset * *end;
}
