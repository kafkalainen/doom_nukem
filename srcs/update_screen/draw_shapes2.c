/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:46:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/19 11:46:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_square(Uint32 *buffer, t_xy offset, int c, int s)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < s)
	{
		x = 0;
		while (x < s)
		{
			put_pixel(buffer, (int)(x + offset.x), (int)(y + offset.y), c);
			x++;
		}
		y++;
	}
}
