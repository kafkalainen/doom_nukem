/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/28 15:17:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_texel	*get_tex(int idx, t_texture	**textures)
{
	if (idx >= 0)
		error_output("idx larger or equal to zero\n");
	idx = -idx;
	return (&textures[idx]->tex);
}

void	add_skybox(t_frame *frame, t_home *home, t_player *plr,
	 t_skybox *skybox)
{
	Uint32	i;

	i = 0;
	quick_reset_queue(frame->transformed);
	while (i < 12)
	{
		if (enqueue_to_raster(frame->transformed, &skybox->face[i]))
		{
			draw_sector(frame, home, plr, frame->idx);
			quick_reset_queue(frame->transformed);
		}
		else
			i++;
	}
}

void	fill_rasterqueue(t_home *home, t_frame *frame, t_player *plr)
{
	add_walls(home, frame, plr);
	add_ground(home, frame, plr);
	add_ceiling(home, frame, plr);
	add_entities(home, frame, plr);
	add_projectiles(home, frame, plr);
}

int	scan_fov(t_home *home, t_fov fov, int sector_count, int **list)
{
	t_uint	i;
	t_wall	*wall;
	t_fov	new_fov;
	t_bool	test[2];

	i = 0;
	wall = home->sectors[fov.cur_sector]->walls;
	*(*list + sector_count) = fov.cur_sector;
	sector_count += 1;
	while (i < home->sectors[fov.cur_sector]->nb_of_walls)
	{
		if (check_if_portal(wall) && !check_if_already_been_in_this_sector(
				wall->top.type, *list, sector_count))
		{
			assign_booleans_for_fov(&test[0], &test[1], fov, wall);
			setup_frame(&new_fov, &fov, wall);
			if (test[0] || test[1])
				sector_count = scan_fov(home, new_fov, sector_count, list);
			else if (check_if_facing_player(test[0], test[1], wall, fov))
				sector_count = scan_fov(home, new_fov, sector_count, list);
		}
		wall = wall->next;
		i++;
	}
	return (sector_count);
}

// //TESTING
// draw_minimap(home, frame);
// draw_player(frame, plr);
// nb_of_sectors = 0;
// frame->fov.pos = vec3_to_vec2(plr->pos);
// // frame->fov.right = vec2_add(frame->fov.pos,
// // vec2_mul(vec2_rot(plr->look2_dir, 1.0472f
// // + ft_fabsf(plr->pitch)), 2000.0f));
// // frame->fov.left = vec2_add(frame->fov.pos,
// // vec2_mul(vec2_rot(plr->look2_dir, -1.0472f
// // - ft_fabsf(plr->pitch)), 2000.0f));
// // frame->fov.right = vec2_add(frame->fov.pos,
// vec2_mul(vec2_rot(plr->look2_dir, 1.0472f), 2000.0f));
// // frame->fov.left = vec2_add(frame->fov.pos,
// vec2_mul(vec2_rot(plr->look2_dir, -1.0472f), 2000.0f));
// frame->fov.right = vec2_add(frame->fov.pos,
// vec2_mul(vec2_rot(plr->look2_dir, FOV), 2000.0f));
// frame->fov.left = vec2_add(frame->fov.pos,
// vec2_mul(vec2_rot(plr->look2_dir, -FOV), 2000.0f));
// draw_left_right(frame, frame->fov.pos,
// frame->fov.left, frame->fov.right, get_color(white));
// // ft_str_pxl(&frame->buffer, vec2(200, 100),
// ft_ftoa(frame->fov.angle, 6), (t_plx_modifier){get_color(white), 2, 10});
// frame->fov.cur_sector = plr->cur_sector;
// nb_of_sectors = scan_fov(home, frame, frame->fov,
// nb_of_sectors, &frame->sector_buffer);
void	draw_game(t_home *home, t_frame *frame, t_player *plr)
{
	int	nb_of_sectors;

	nb_of_sectors = 0;
	quick_reset_queue(frame->transformed);
	plr->look2_dir = vec2_unit_vector(vec2(plr->look_dir.x, plr->look_dir.z));
	frame->fov.pos = vec3_to_vec2(plr->pos);
	frame->fov.right = vec2_add(frame->fov.pos,
			vec2_mul(vec2_rot(plr->look2_dir, FOV), 2000.0f));
	frame->fov.left = vec2_add(frame->fov.pos,
			vec2_mul(vec2_rot(plr->look2_dir, -FOV), 2000.0f));
	frame->fov.cur_sector = plr->cur_sector;
	nb_of_sectors = scan_fov(home, frame->fov, nb_of_sectors,
			&frame->sector_buffer);
	add_skybox(frame, home, plr, &home->skybox);
	while (nb_of_sectors--)
	{
		frame->idx = frame->sector_buffer[nb_of_sectors];
		fill_rasterqueue(home, frame, plr);
		if (frame->transformed->size > 0)
			draw_sector(frame, home, plr, frame->idx);
	}
}
