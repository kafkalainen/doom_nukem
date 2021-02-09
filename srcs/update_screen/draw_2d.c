/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/09 09:56:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_2d_fov(t_frame *frame, t_player *plr)
{
	t_xy fov_left;
	t_xy fov_right;
	t_xy offset;
	t_xy plr_pos;

	plr_pos = plr->pos;
	offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	fov_left = vec2_rot(plr->dir, DEG_TO_RAD * -FOV * 0.5);
	fov_right = vec2_rot(plr->dir, DEG_TO_RAD * FOV * 0.5);
	draw_rect_center(vec2_add(vec2(0,0), offset), vec2(5, 5), frame);
	ft_draw_line(vec2_add(plr_pos, offset), vec2_add(vec2_add(plr_pos, vec2_mul(fov_left, 400)), offset), lightgreen, frame->draw_surf);
	ft_draw_line(vec2_add(plr_pos, offset), vec2_add(vec2_add(plr_pos, vec2_mul(fov_right, 400)), offset), lightgreen, frame->draw_surf);
}

/* 1. Test if leftmost ray hits the polygon.
** YES: Move to the next phase
** NO: Move to next polygon.
** 2. Test if rightmost ray hits the polygon.
** YES: Draw the space between.
** NO: Draw to the end of the polygon.
** 3. Move to the next polygon.
*/

void			draw_text(t_home *home, char *text, t_frame *frame, t_xy pos)
{
	SDL_Rect	rect;

	SDL_Color color = {255, 80, 0, 0};
	home->text_surf = TTF_RenderText_Solid(home->font, text, color);
	rect.x = pos.x;
	rect.y = pos.y;
	SDL_BlitSurface(home->text_surf, NULL, frame->draw_surf, &rect);
	SDL_FreeSurface(home->text_surf);
}

int				hypotenuse(int opposite, int adjacent)
{
	return (sqrt(opposite * opposite + adjacent * adjacent));
}

void			draw_2d(t_home *home, t_frame *frame, t_player *plr)
{
	frame->idx = 0;
	frame->old_idx = -1;
	frame->max_fov = FOV * DEG_TO_RAD;
	frame->offset = 0;
	frame->plr_offset = vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
	scan_fov(home, frame);
	draw_2d_fov(frame, plr);
}

// void			perspective_transformation(t_point *x0, t_point *x1, t_home *home, int idx)
// {
// 	float	wall_height_y1a;
// 	float	wall_height_y1b;
// 	float	wall_height_y2a;
// 	float	wall_height_y2b;
// 	float	wall_width_x1;
// 	float	wall_width_x2;

// 	wall_height_y1a = home->sectors[idx]->ceiling / x0->x0.y * SCREEN_HEIGHT;
// 	wall_height_y1b = -home->sectors[idx]->ceiling / x0->x0.y * SCREEN_HEIGHT;
// 	wall_height_y2a = home->sectors[idx]->ceiling / x1->x0.y * SCREEN_HEIGHT;
// 	wall_height_y2b = -home->sectors[idx]->ceiling / x1->x0.y * SCREEN_HEIGHT;
// 	wall_width_x1 = x0->x0.x / x0->x0.y * SCREEN_WIDTH;
// 	wall_width_x2 = x1->x0.x / x1->x0.y * SCREEN_WIDTH;
// 	ft_draw_line(vec2_add(vec2(wall_width_x1, wall_height_y1a), home->offset), vec2_add(vec2(wall_width_x2, wall_height_y2a), home->offset), 0xFF8000, home->draw_surf);
// 	ft_draw_line(vec2_add(vec2(wall_width_x1, wall_height_y1b), home->offset), vec2_add(vec2(wall_width_x2, wall_height_y2b), home->offset), 0xFF8000, home->draw_surf);
// 	ft_draw_line(vec2_add(vec2(wall_width_x1, wall_height_y1a), home->offset), vec2_add(vec2(wall_width_x1, wall_height_y1b), home->offset), 0xFF8000, home->draw_surf);
// 	ft_draw_line(vec2_add(vec2(wall_width_x2, wall_height_y2a), home->offset), vec2_add(vec2(wall_width_x2, wall_height_y2b), home->offset), 0xFF8000, home->draw_surf);
// }

// void			perspective_transformation(t_point *p0, t_point *p1, t_home *home, int idx)
// {
// 	t_xyz	screen;
// 	t_xyz	screen2;
// 	t_xyz	mirror;
// 	t_xyz	mirror2;

// 	screen.x = p0->x0.x;
// 	screen.y = home->sectors[idx]->ceiling * 100;
// 	screen.z = p0->x0.y;
// 	screen2.x = p1->x0.x;
// 	screen2.y = home->sectors[idx]->ceiling * 100;
// 	screen2.z = p1->x0.y;
// 	screen.x = 1.33333333333 * screen.x / screen.z;
// 	screen.y = screen.y / screen.z;
// 	mirror.y = -screen.y / screen.z;
// 	screen2.x = 1.33333333333 * screen2.x / screen2.z;
// 	screen2.y = screen2.y / screen2.z;
// 	mirror2.y = -screen2.y / screen2.z;
// 	ft_draw_line(vec2_add(vec2(screen.x, screen.y), home->offset), vec2_add(vec2(screen2.x, screen2.y), home->offset), 0xFF8000, home->draw_surf);
// 	ft_draw_line(vec2_add(vec2(screen.x, mirror.y), home->offset), vec2_add(vec2(screen2.x, mirror2.y), home->offset), 0xFF8000, home->draw_surf);
// }
