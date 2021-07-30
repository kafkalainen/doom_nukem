/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:12:34 by tmaarela          #+#    #+#             */
/*   Updated: 2021/07/30 15:16:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_wall		*wall_hit(t_wall *wall, unsigned int nb_of_walls,
					t_xy pos, t_xy dir)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_walls)
	{
		if (check_intersection(wall, pos, dir))
			return (wall);
		wall = wall->next;
		i++;
	}
	return (NULL);
}

static t_xyz		get_bullet_hit_point(t_home *home, t_player *plr)
{
	t_wall			*wall;
	t_xyz			dir;
	t_plane			plane;
	t_xyz			pos;
	t_xy			pos_2;
	t_xy			dir_2;

	pos = plr->pos;
	dir = vec3_unit_vector(plr->look_dir);
	pos_2 = (t_xy){plr->pos.x, plr->pos.z};
	dir_2 = vec2_mul((t_xy){dir.x, dir.z}, 5.0f);
	wall = home->sectors[plr->cur_sector]->walls;
	wall = wall_hit(wall, home->sectors[plr->cur_sector]->nb_of_walls,
		pos_2, dir_2);
	if (!wall)
		printf("NO POINT");
	else
	{
		plane.point = wall->top.p[0];
		plane.normal = wall->top.normal;
		pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
		printf("START\n%f\n%f\n%f\n%d--\n", pos.x, pos.y, pos.z, wall->top.idx);
		home->entity_pool[0]->pos = pos;
		home->entity_pool[0]->dir = wall->top.normal;
	}
	return (pos);
}

void			shooting_handle(t_home *home, t_player *plr)
{
//	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	get_bullet_hit_point(home, plr);
}
