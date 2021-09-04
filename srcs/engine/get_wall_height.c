/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 10:41:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/04 09:31:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_wall_height(float left_ground, float right_ground,
	float left_ceiling, float right_ceiling)
{
	float	max_ceiling;
	float	min_ground;

	if (left_ceiling > right_ceiling)
		max_ceiling = left_ceiling;
	else
		max_ceiling = right_ceiling;
	if (left_ground < right_ground)
		min_ground = left_ground;
	else
		min_ground = right_ground;
	return (max_ceiling - min_ground);
}
