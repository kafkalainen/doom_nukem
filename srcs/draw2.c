/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:17:42 by tmaarela          #+#    #+#             */
/*   Updated: 2020/12/14 15:17:42 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

void	draw_rect(t_xy xy, t_xy wh, t_home *home, int color)
{
	double j;
	double i;

	i = xy.x;
	j = xy.y;
	while (j < wh.y + xy.y)
	{
		ft_draw_line(vec2(i, j), vec2(i + wh.x, j), color, home->surf);
		j++;
	}
}
