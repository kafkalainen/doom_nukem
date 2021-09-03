/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hurt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:18:23 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 14:19:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_hurt(t_frame *frame)
{
	unsigned int	i;

	i = 0;
	while (i < SCREEN_HEIGHT * SCREEN_WIDTH)
	{
		*(frame->buffer + i) = red;
		i++;
	}
}
