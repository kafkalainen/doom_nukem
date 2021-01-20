/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/20 16:26:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_2d(t_home *home, t_player *plr)
{
	int i;
	t_polygon	*temp;

	i = 1;
	temp = home->sectors[0]->polygons;
	while (temp->next)
	{
		if (temp->idx > 0)
		{
			ft_draw_line(
				temp->x0,
				temp->next->x0,
				0xFF00FF,
				home->draw_surf
			);
		}
		temp = temp->next;
		i++;
	}
	ft_draw_line(temp->x0, home->sectors[0]->polygons->x0, 0xFF00FF, home->draw_surf);
	plr->pos = vec2(plr->pos.x, plr->pos.y);
	plr->dir = vec2(plr->dir.x, plr->dir.y);
	draw_rect_center(plr->pos, vec2(5, 5), home);
	ft_draw_line(plr->pos, vec2_add(plr->pos, plr->dir), 0xA8C256, home->draw_surf);
}
