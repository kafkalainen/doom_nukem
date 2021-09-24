/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:40:15 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 17:59:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	resize_portal(t_wall *front, t_wall *behind, char c)
{
	float	min_ceil[2];

	if (c == 't')
	{
		min_ceil[0] = ft_fmin(front->top.p[1].y, behind->top.p[2].y);
		min_ceil[1] = ft_fmin(front->top.p[2].y, behind->top.p[1].y);
		behind->top.p[2].y = min_ceil[0];
		behind->top.p[1].y = min_ceil[1];
		behind->bot.p[1].y = min_ceil[0];
	}
	else
	{
		min_ceil[0] = ft_fmax(front->bot.p[0].y, behind->bot.p[2].y);
		min_ceil[1] = ft_fmax(front->bot.p[2].y, behind->bot.p[0].y);
		behind->bot.p[2].y = min_ceil[0];
		behind->bot.p[0].y = min_ceil[1];
		behind->top.p[0].y = min_ceil[1];
	}
}
