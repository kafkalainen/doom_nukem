/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 08:46:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 09:09:27 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_screen_xy	round_coordinates(t_xy	coord)
{
	t_xy		remainder;
	t_screen_xy	new_coord;

	remainder.x = coord.x - (int)coord.x;
	remainder.y = coord.y - (int)coord.y;
	if (remainder.x > -0.5f && remainder.x <= 0.0f)
		new_coord.x = (int)coord.x;
	if (remainder.x > -1.0f && remainder.x <= -0.5f)
		new_coord.x = (int)coord.x - 1.0f;
	if (remainder.y > -0.5f && remainder.y <= 0.0f)
		new_coord.y = (int)coord.y;
	if (remainder.y > -1.0f && remainder.y <= -0.5f)
		new_coord.y = (int)coord.y - 1.0f;
	if (remainder.x >= 0.0f && remainder.x < 0.5f)
		new_coord.x = (int)coord.x;
	if (remainder.x >= 0.5f && remainder.x < 1.0f)
		new_coord.x = (int)coord.x + 1.0f;
	if (remainder.y >= 0.0f && remainder.y < 0.5f)
		new_coord.y = (int)coord.y;
	if (remainder.y >= 0.5f && remainder.y < 1.0f)
		new_coord.y = (int)coord.y + 1.0f;
	return (new_coord);
}
