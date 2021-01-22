/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/22 10:10:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_2d(t_home *home, t_player *plr, t_intersection *sect)
{
	int i;
	t_polygon	*temp;
	t_polygon	*perkele;
	t_xy		dir;

	i = 0;
	while(i < 2)
	{
		temp = home->sectors[i]->polygons;
		while (temp)
		{
			if (temp->idx)
			{
				perkele = (temp->next == NULL) ? home->sectors[i]->polygons : temp->next;
				calc_intersection(temp, home->sectors[i]->polygons, plr, sect);
				ft_draw_line(
					temp->x0, perkele->x0, fuchsia, home->draw_surf);
			}
			if (temp->idx > -1)
				draw_rect_center(line_intersection(sect), vec2(16, 16), home);
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		i++;
	}
	//ft_draw_line(temp->x0, home->sectors[0]->polygons->x0, fuchsia, home->draw_surf);
	draw_rect_center(plr->pos, vec2(5, 5), home);
	dir = vec2(plr->dir.x * MINIMAP_SIZE, plr->dir.y * MINIMAP_SIZE);
	ft_draw_line(plr->pos, vec2_add(plr->pos, vec2_mul(dir, 20)), lightgreen, home->draw_surf);
}
