/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:12:34 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/28 19:12:34 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_xyz		get_bullet_hit_point(t_home *home, t_player *plr)
{
	t_xyz			pos;
	t_xyz			dir;
	t_xyz			ret;
	t_plane			plane;
	t_wall			wall;
	unsigned int	i;

	pos = plr->pos;
	dir = vec3_dec(vec3_add(plr->pos, plr->look_dir), plr->pos);
	i = 0;
	ret = (t_xyz){0,0,0};
	while (i < home->sectors[plr->cur_sector]->nb_of_walls)
	{
		if (point_inside_a_triangle_wall(home->sectors[plr->cur_sector]->walls->top.p[0],
			home->sectors[plr->cur_sector]->walls->top.p[1],
			home->sectors[plr->cur_sector]->walls->top.p[2],
			pos))
		{
			printf("START\n%f\n%f\n%f\n%p--\n", ret.x, ret.y, ret.z, home->sectors[plr->cur_sector]->walls);
			return (ret);
		}
		else
			printf("miss\n");
		plane = (t_plane){home->sectors[plr->cur_sector]->walls->top.p[0],
			home->sectors[plr->cur_sector]->walls->top.normal};
		ret = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
		i++;
		home->sectors[plr->cur_sector]->walls = home->sectors[plr->cur_sector]->walls->next;
	}
	return ret;
}

void			shooting_handle(t_home *home, t_player *plr)
{
//	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	get_bullet_hit_point(home, plr);
}