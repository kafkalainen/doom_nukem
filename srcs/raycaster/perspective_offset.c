/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_offset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:04:55 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 16:15:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float			perspective_offset(float frame_offset, int screen_wall)
{
	float		left_mult;
	float		right_mult;

	left_mult = SCREEN_WIDTH - frame_offset;
	right_mult = SCREEN_WIDTH - frame_offset + screen_wall;
	if (left_mult <= 320)
		left_mult = ((0.5 * SCREEN_WIDTH - left_mult) * 0.00129441738f + 1);
	else
		left_mult = ((left_mult - 0.5 * SCREEN_WIDTH) * 0.00129441738f + 1);
	if (right_mult <= 320)
		right_mult = ((0.5 * SCREEN_WIDTH - right_mult) * 0.00129441738f + 1);
	else
		right_mult = ((right_mult - 0.5 * SCREEN_WIDTH) * 0.00129441738f + 1);
	return ((right_mult + left_mult) / 2);
}
