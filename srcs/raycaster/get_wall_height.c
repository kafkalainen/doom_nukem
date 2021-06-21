/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 10:41:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/21 11:34:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_wall_height(Uint32 left_ground, Uint32 right_ground,
	Uint32 left_ceiling, Uint32 right_ceiling)
{
	float	max_ceiling;
	float	max_ground;

	if (left_ceiling > right_ceiling)
		max_ceiling = left_ceiling;
	else
		max_ceiling = left_ceiling;
	if (left_ground < right_ground)
		max_ground = left_ground;
	else
		max_ground = right_ground;
	return (max_ceiling - max_ground);
}
