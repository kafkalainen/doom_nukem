/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/26 18:01:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_2d_fov(t_home *home, t_player *plr)
{
	t_xy fov_left;
	t_xy fov_right;
	t_xy dir;

	dir = vec2(plr->dir.x * MINIMAP_SIZE, plr->dir.y * MINIMAP_SIZE);
	fov_left = vec2_rot(dir, DEG_TO_RAD * -FOV * 0.5);
	fov_right = vec2_rot(dir, DEG_TO_RAD * FOV * 0.5);
	ft_draw_line(plr->pos, vec2_add(plr->pos, vec2_mul(fov_left, 20)), lightgreen, home->draw_surf);
	ft_draw_line(plr->pos, vec2_add(plr->pos, vec2_mul(fov_right, 20)), lightgreen, home->draw_surf);
	ft_draw_line(plr->pos, vec2_add(plr->pos, vec2_mul(dir, 20)), lightgreen, home->draw_surf);
}

/* 1. Test if leftmost ray hits the polygon.
** YES: Move to the next phase
** NO: Move to next polygon.
** 2. Test if rightmost ray hits the polygon.
** YES: Draw the space between.
** NO: Draw to the end of the polygon.
** 3. Move to the next polygon.
*/


void			draw_2d(t_home *home, t_player *plr, t_intersection *sect)
{
	int i;
	t_polygon	*temp;
	t_polygon	*perkele;
	t_xy		dir;
	t_ray_fov	fov;

	i = 0;
	while(i < 2)
	{
		temp = home->sectors[i]->polygons;
		while (temp)
		{
			if (temp->idx)
			{
				perkele = (temp->next == NULL) ? home->sectors[i]->polygons : temp->next;
				fov = get_fov_points(temp, home, plr, i);
				if (fov.left_point.x > 0)
				{
					if (fov.right_point.x > 0)
						ft_draw_line(fov.left_point, fov.right_point, green, home->draw_surf);
					else
						ft_draw_line(fov.left_point, perkele->x0, green, home->draw_surf);
				}
			}
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		i++;
	}
	//ft_draw_line(temp->x0, home->sectors[0]->polygons->x0, fuchsia, home->draw_surf);
	draw_rect_center(plr->pos, vec2(5, 5), home);
	draw_2d_fov(home, plr);
}
