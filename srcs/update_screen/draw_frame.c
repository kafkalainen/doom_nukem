/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/19 11:57:41 by jnivala          ###   ########.fr       */
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

/*
**		draw_line(
**			center_to_screen(home->sectors[i]->floor_bottom_left),
**			center_to_screen(home->sectors[i]->floor_bottom_right),
**			red, frame->buffer);
**		draw_line(
**			center_to_screen(home->sectors[i]->floor_top_left),
**			center_to_screen(home->sectors[i]->floor_top_right),
**			red, frame->buffer);
**		draw_line(
**			center_to_screen(home->sectors[i]->floor_top_left),
**			center_to_screen(home->sectors[i]->floor_bottom_left),
**			red, frame->buffer);
**		draw_line(
**			center_to_screen(home->sectors[i]->floor_top_right),
**			center_to_screen(home->sectors[i]->floor_bottom_right),
**			red, frame->buffer);
*/
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

static void	draw_player(t_frame *frame)
{
	draw_square(frame->buffer, center_to_screen((t_xy){-2.0f, -2.0f}),
		yellow, 4);
	draw_line(center_to_screen((t_xy){0.0f, 0.0f}),
		center_to_screen(vec2_add((t_xy){0.0f, 0.0f},
				vec2_mul((t_xy){-PLR_DIR, PLR_DIR}, 400))),
		lightgreen, frame->buffer);
	draw_line(center_to_screen((t_xy){0.0f, 0.0f}),
		center_to_screen(vec2_add((t_xy){0.0f, 0.0f},
				vec2_mul((t_xy){PLR_DIR, PLR_DIR}, 400))),
		lightgreen, frame->buffer);
}

static void	draw_info(t_frame *frame, t_player *plr, int nb_fps)
{
	char			*sector;
	char			*compass;
	char			*fps;
	char			*plr_z;
	t_plx_modifier	mod;

	mod.colour = white;
	mod.size = TEXT_SIZE;
	compass = compass_direction(&plr->dir);
	sector = ft_itoa(plr->current_sector);
	fps = ft_itoa(nb_fps);
	plr_z = ft_ftoa(plr->z, 6);
	str_pxl(frame->buffer, (t_xy){SCREEN_WIDTH * 0.5 - 15, 0}, fps, mod);
	str_pxl(frame->buffer, (t_xy){0, 50}, "dir: ", mod);
	str_pxl(frame->buffer, (t_xy){50, 50}, compass, mod);
	str_pxl(frame->buffer, (t_xy){0, 70}, "sector:", mod);
	str_pxl(frame->buffer, (t_xy){0, 90}, sector, mod);
	str_pxl(frame->buffer, (t_xy){0, 110}, "current_z:", mod);
	str_pxl(frame->buffer, (t_xy){0, 130}, plr_z, mod);
	str_pxl(frame->buffer, (t_xy){0, 380}, "z to switch to wireframe", mod);
	str_pxl(frame->buffer, (t_xy){0, 400}, "x to close minimap", mod);
	str_pxl(frame->buffer, (t_xy){0, 420}, "c to close info", mod);
	str_pxl(frame->buffer, (t_xy){0, 440}, "wasd, rotate with q and e.", mod);
	str_pxl(frame->buffer, (t_xy){0, 460}, "free mouse with m", mod);
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
		draw_player(frame);
	}
	if (plr->input.info)
		draw_info(frame, plr, (int)home->t.fps);
	return ;
}
