/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ndc_to_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:47:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/08 15:54:31 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_xy	ndc_to_world(t_xy ndc, t_xy offset, float scalar)
{
	float	denom;
	t_xy	world_coord;

	denom = 1 / scalar;
	world_coord = vec2_mul(ndc, denom);
	offset = vec2_mul(offset, -denom);
	world_coord = vec2_add(offset, world_coord);
	return (world_coord);
}
