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

//static int evaluate_ret(t_xyz a, t_xyz b)
//{
//	if (a.x == b.x && a.y == b.y && a.z == b.z)
//		return (TRUE);
//	return (FALSE);
//}

static t_xyz		get_bullet_hit_point(t_home *home, t_player *plr)
{
	unsigned int	i;
	t_wall			*walls;
	t_xyz			dir;
	t_plane			plane;
	t_xyz			pos;

	pos = plr->pos;
	i = 0;
	dir = vec3_unit_vector(plr->look_dir);
	walls = home->sectors[plr->cur_sector]->walls;
	while (i < home->sectors[plr->cur_sector]->nb_of_walls)
	{
		if (point_inside_a_triangle_wall(walls->top.p[0],
				walls->top.p[1], walls->top.p[2], pos));
			break ;
		printf("old wall: %p\n", walls);
		walls = walls->next;
		printf("new wall: %p\n", walls);
		i++;
	}
	plane.point = walls->top.p[0];
	plane.normal = walls->top.normal;
	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	printf("START\n%f\n%f\n%f\n%d--\n", pos.x, pos.y, pos.z, walls->top.idx);
	home->entity_pool[0]->pos = pos;

	return (pos);
//	t_xyz			pos;
//	t_xyz			dir;
//	t_xyz			ret;
//	t_plane			plane;
//	t_wall			*wall;
//	unsigned int	i;
//
//	pos = plr->pos;
//	dir = vec3_unit_vector(plr->look_dir);
//	dir = vec3_add(pos, vec3_mul(dir, 10.0f));
//	wall = home->sectors[plr->cur_sector]->walls;
//	i = 0;
//	ret = (t_xyz){0,0,0};
//	while (i < home->sectors[plr->cur_sector]->nb_of_walls)
//	{
//		plane.point = wall->top.p[0];
//		plane.normal = wall->top.normal;
//		ret = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
//		if (evaluate_ret(ret, pos) == FALSE)
//		{
//			printf("START\n%f\n%f\n%f\n%d--\n", ret.x, ret.y, ret.z, wall->top.idx);
//			printf("LOOK\n%f\n%f\n%f\n%d--\n", plr->look_dir.x, plr->look_dir.y, plr->look_dir.z);
//			home->entity_pool[0]->pos = ret;
//			return (ret);
//		}
//		else
//			printf("miss\n");
//		i++;
//		wall = wall->next;
//	}
//	free(wall);
//	return ret;
}

void			shooting_handle(t_home *home, t_player *plr)
{
//	pos = vec3_intersection_with_ray_and_plane(&plane, pos, dir);
	get_bullet_hit_point(home, plr);
}
