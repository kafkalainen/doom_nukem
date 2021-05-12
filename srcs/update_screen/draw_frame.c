/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/12 16:38:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static char	*compass_direction(t_xy *dir)
{
	if (dir->x <= NW && dir->x > 0)
		return (ft_strdup("North"));
	else if (dir->x <= N && dir->x > NE)
		return (ft_strdup("North"));
	else if (dir->x <= SW && dir->x > NW)
		return (ft_strdup("West"));
	else if (dir->x <= SE && dir->x > SW)
		return (ft_strdup("South"));
	else if (dir->x <= NE && dir->x > SE)
		return (ft_strdup("East"));
	else
		return (ft_strdup("NO DIR"));
}

static void	draw_minimap(t_home *home, t_frame *frame)
{
	unsigned int	i;
	unsigned int	j;
	t_point			*temp;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		j = 0;
		temp = home->sectors[i]->points;
		draw_line(
			center_to_screen(home->sectors[i]->floor_bottom_left),
			center_to_screen(home->sectors[i]->floor_bottom_right),
			red, frame->buffer);
		draw_line(
			center_to_screen(home->sectors[i]->floor_top_left),
			center_to_screen(home->sectors[i]->floor_top_right),
			red, frame->buffer);
		draw_line(
			center_to_screen(home->sectors[i]->floor_top_left),
			center_to_screen(home->sectors[i]->floor_bottom_left),
			red, frame->buffer);
		draw_line(
			center_to_screen(home->sectors[i]->floor_top_right),
			center_to_screen(home->sectors[i]->floor_bottom_right),
			red, frame->buffer);
		while (j < home->sectors[i]->nb_of_walls)
		{
			draw_line(center_to_screen(temp->x0),
				center_to_screen(temp->next->x0),
				greenyellow, frame->buffer);
			temp = temp->next;
			j++;
		}
		i++;
	}
}

static void	draw_player(t_frame *frame, t_player *plr)
{
	plr = plr;
	// draw_line(center_to_screen((t_xy){0.0f, 0.0f}),
	// 	center_to_screen(vec2_mul(plr->dir, 400)), lightgreen,
	// 	frame->buffer);
	draw_rect(center_to_screen((t_xy){0.0f, 0.0f}),
		(t_xy){3.0f, 3.0f}, frame->buffer, yellow);
	draw_line(center_to_screen((t_xy){0.0f, 0.0f}),
		center_to_screen(vec2_add((t_xy){0.0f, 0.0f},
				vec2_mul((t_xy){1.0f, 0.0f}, 400))),
		lightgreen, frame->buffer);
	draw_line(center_to_screen((t_xy){0.0f, 0.0f}),
		center_to_screen(vec2_add((t_xy){0.0f, 0.0f},
				vec2_mul((t_xy){0.0f, 1.0f}, 400))),
		lightgreen, frame->buffer);
}

static void	draw_info(t_frame *frame, t_player *plr, int nb_fps)
{
	char	*sector;
	char	*compass;
	char	*fps;
	char	*plr_z;

	compass = compass_direction(&plr->dir);
	sector = ft_itoa(plr->current_sector);
	fps = ft_itoa(nb_fps);
	str_pxl(frame->buffer, (t_xy){SCREEN_WIDTH * 0.5 - 15, 0}, fps, white);
	str_pxl(frame->buffer, (t_xy){0, 50}, "dir: ", white);
	str_pxl(frame->buffer, (t_xy){50, 50}, compass, white);
	str_pxl(frame->buffer, (t_xy){0, 70}, "sector:", white);
	str_pxl(frame->buffer, (t_xy){0, 90}, sector, white);
	str_pxl(frame->buffer, (t_xy){0, 380}, "Press z to switch to wireframe", white);
	str_pxl(frame->buffer, (t_xy){0, 400}, "Press x to close minimap", white);
	str_pxl(frame->buffer, (t_xy){0, 420}, "Press c to close info", white);
	str_pxl(frame->buffer, (t_xy){0, 440}, "Move with wasd, rotate with q and e.", white);
	str_pxl(frame->buffer, (t_xy){0, 460}, "Capture and free mouse with m", white);
	free(fps);
	free(sector);
	free(compass);
	free(plr_z);
}

void	draw_frame(t_home *home, t_frame *frame, t_player *plr)
{
	frame->idx = plr->current_sector;
	frame->old_idx = old_sector;
	frame->max_fov = 0;
	frame->offset = 640;
	frame->pxl_offset = 0.0f;
	frame->left.l_pt = (t_xy){-1.0f, -1.0f};
	frame->right.r_pt = (t_xy){-1.0f, -1.0f};
	scan_fov(home, frame, plr, 0);
	if (plr->input.minimap)
	{
		draw_minimap(home, frame);
		draw_player(frame, plr);
	}
	if (plr->input.info)
		draw_info(frame, plr, (int)home->t.fps);
	return ;
}
