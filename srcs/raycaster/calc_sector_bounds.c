/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sector_bounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:22:44 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/02 15:27:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
**	ERRORZ
**
*/
// #include "../../headers/doom_nukem.h"

// static void	init_sector_bounds(t_ceiling *ceiling, t_ground *ground, t_xyz *value)
// {
// 	ceiling->top.p[0] = *value;
// 	ceiling->top.p[1] = *value;
// 	ceiling->top.p[2] = *value;
// 	ceiling->bottom.p[0] = *value;
// 	ceiling->bottom.p[1] = *value;
// 	ceiling->bottom.p[2] = *value;
// 	ground->top.p[0] = *value;
// 	ground->top.p[1] = *value;
// 	ground->top.p[2] = *value;
// 	ground->top.colour = purple;
// 	ground->bottom.p[0] = *value;
// 	ground->bottom.p[1] = *value;
// 	ground->bottom.p[2] = *value;
// 	ground->bottom.colour = purple;
// }

// static void	find_biggest_square(t_sector *sector)
// {
// 	size_t	walls;
// 	t_wall	*temp;

// 	walls = sector->nb_of_walls;
// 	temp = sector->walls;
// 	while (walls)
// 	{
// 		if (temp->top.p[0].x < sector->ground.top.p[1].x)
// 			sector->ground.top.p[1].x = temp->top.p[0].x;
// 		if (temp->top.p[0].x > sector->ground.top.p[0].x)
// 			sector->ground.top.p[0].x = temp->top.p[0].x;
// 		if (temp->top.p[0].z < sector->ground.top.p[2].z)
// 			sector->ground.top.p[2].z = temp->top.p[0].z;
// 		if (temp->top.p[0].z > sector->ground.top.p[0].z)
// 			sector->ground.top.p[0].z = temp->top.p[0].z;
// 		temp = temp->next;
// 		walls--;
// 	}
// 	sector->ground.top.p[0].x = sector->ground.top.p[1].x;
// 	sector->ground.bottom.p[0].x = sector->ground.top.p[1].x;
// 	sector->ground.bottom.p[1].x = sector->ground.top.p[2].x;
// 	sector->ground.bottom.p[2].x = sector->ground.bottom.p[1].x;
// 	sector->ground.top.p[1].z = sector->ground.top.p[2].z;
// 	sector->ground.bottom.p[1].z = sector->ground.top.p[2].z;
// 	sector->ground.bottom.p[0].z = sector->ground.top.p[0].z;
// }

// static void	init_texels_at_ground(t_ground *ground)
// {
// 	ground->top.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
// 	ground->top.uv[1] = (t_uvz){0.0f, 0.0f, 1.0f};
// 	ground->top.uv[2] = (t_uvz){1.0f, 0.0f, 1.0f};
// 	ground->bottom.uv[0] = (t_uvz){0.0f, 1.0f, 1.0f};
// 	ground->bottom.uv[1] = (t_uvz){1.0f, 1.0f, 1.0f};
// 	ground->bottom.uv[2] = (t_uvz){1.0f, 0.0f, 1.0f};
// }

// static void	init_ceiling(t_ceiling *ceiling, t_ground *ground)
// {
// 	ceiling->top.p[0] = ground->top.p[0];
// 	ceiling->top.p[1] = ground->top.p[1];
// 	ceiling->top.p[2] = ground->top.p[2];
// 	ceiling->bottom.p[0] = ground->bottom.p[0];
// 	ceiling->bottom.p[1] = ground->bottom.p[1];
// 	ceiling->bottom.p[2] = ground->bottom.p[2];
// 	ceiling->top.uv[0] = ground->top.uv[0];
// 	ceiling->top.uv[1] = ground->top.uv[1];
// 	ceiling->top.uv[2] = ground->top.uv[2];
// 	ceiling->bottom.uv[0] = ground->bottom.uv[0];
// 	ceiling->bottom.uv[1] = ground->bottom.uv[1];
// 	ceiling->bottom.uv[2] = ground->bottom.uv[2];
// }

// void	calc_sector_bounds(t_sector *sector)
// {
// 	init_sector_bounds(&sector->ceiling, &sector->ground, &sector->walls->top.p[0]);
// 	find_biggest_square(sector);
// 	init_texels_at_ground(&sector->ground);
// 	init_ceiling(&sector->ceiling, &sector->ground);
// }
