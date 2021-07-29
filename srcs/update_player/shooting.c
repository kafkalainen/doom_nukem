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

static int evaluate_ret(t_xyz a, t_xyz b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (TRUE);
	return (FALSE);
}

static t_xyz		get_bullet_hit_point(t_home *home, t_player *plr)
{
	t_xyz			pos;
	t_xyz			dir;
	t_xyz			ret;
	t_plane			plane;
	t_wall			*wall;
	unsigned int	i;

	pos = plr->pos;
	dir = plr->look_dir;
	wall = home->sectors[plr->cur_sector]->walls;
	i = 0;
	ret = (t_xyz){0,0,0};
	while (i < home->sectors[plr->cur_sector]->nb_of_walls)
	{
		plane.point = wall->top.p[0];
		plane.normal = wall->top.normal;
		ret = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
		if (evaluate_ret(ret, pos) == FALSE)
		{
			printf("START\n%f\n%f\n%f\n%d--\n", ret.x, ret.y, ret.z, wall->top.idx);
			return (ret);
		}
		else
			printf("miss\n");
		i++;
		wall = wall->next;
	}
	free(wall);
	return ret;
}

void			shooting_handle(t_home *home, t_player *plr)
{
//	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	get_bullet_hit_point(home, plr);
}
