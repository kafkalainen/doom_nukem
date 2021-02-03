/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/03 10:07:58 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			draw_2d_fov(t_home *home, t_player *plr)
{
	t_xy fov_left;
	t_xy fov_right;
	t_xy dir;
	t_xy offset;

	offset = vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	dir = vec2(plr->dir.x * MINIMAP_SIZE, plr->dir.y * MINIMAP_SIZE);
	fov_left = vec2_rot(dir, DEG_TO_RAD * -FOV * 0.5);
	fov_right = vec2_rot(dir, DEG_TO_RAD * FOV * 0.5);
	draw_rect_center(vec2_add(plr->pos, offset), vec2(5, 5), home);
	// ft_draw_line(vec2_add(plr->pos, offset), vec2_add(vec2_add(plr->pos, vec2_mul(fov_left, 20)), offset), lightgreen, home->draw_surf);
	// ft_draw_line(vec2_add(plr->pos, offset), vec2_add(vec2_add(plr->pos, vec2_mul(fov_right, 20)), offset), lightgreen, home->draw_surf);
	ft_draw_line(vec2_add(plr->pos, offset), vec2_add(vec2_add(plr->pos, vec2_mul(dir, 20)), offset), lightgreen, home->draw_surf);
}

/* 1. Test if leftmost ray hits the polygon.
** YES: Move to the next phase
** NO: Move to next polygon.
** 2. Test if rightmost ray hits the polygon.
** YES: Draw the space between.
** NO: Draw to the end of the polygon.
** 3. Move to the next polygon.
*/

void			draw_text(t_home *home, char *text, t_xy pos)
{
	SDL_Rect	rect;

	SDL_Color color = {255, 80, 0, 0};
	home->text_surf = TTF_RenderText_Solid(home->font, text, color);
	rect.x = pos.x;
	rect.y = pos.y;
	SDL_BlitSurface(home->text_surf, NULL, home->draw_surf, &rect);
	SDL_FreeSurface(home->text_surf);
}

int				hypotenuse(int opposite, int adjacent)
{
	return (sqrt(opposite * opposite + adjacent * adjacent));
}

void			draw_angles(t_home *home, t_sector *sector, t_ray_fov *fov)
{
	t_point		*current;

	calc_angles(fov, sector);
	ft_draw_line(vec2_add(vec2(0,0), home->offset), vec2_add(fov->left_point, home->offset), pink, home->draw_surf);
	ft_draw_line(vec2_add(vec2(0,0), home->offset), vec2_add(fov->right_point, home->offset), pink, home->draw_surf);
	current = loop_list(sector->points, fov->left_wall->next);
	while (current != fov->right_wall)
	{
		ft_draw_line(vec2_add(vec2(0,0), home->offset), vec2_add(current->x0, home->offset), pink, home->draw_surf);
		current = loop_list(sector->points, current->next);
	}
	// while (temp)
	// {
	// 	draw_text(home, ft_ftoa(sector->points->wall_rad, 5, '.'), vec2_add(temp->x0, home->offset));

	// 	temp = temp->next;
	// }
}

void			draw_2d(t_home *home, t_player *plr)
{
	int i;
	t_point		*p0;
	t_point		*p1;
	t_ray_fov	fov;

	i = 0;
	// while(i < 2)
	// {
	// translate_world_view(plr, home);
	p0 = home->sectors[i]->points;
	fov = get_fov(home, plr, i);
	draw_angles(home, home->sectors[i], &fov);
	while (p0)
		{
			if (p0->idx)
			{
				p1 = (p0->next == NULL) ? home->sectors[i]->points : p0->next;
				if (p0->x0.y >= 0 || p1->x0.y >= 0)
				{
					// draw_text(home, ft_ftoa(vec2_angle(p0->x0, p1->x0), 5, '.'), vec2_add(p0->x0, home->offset));
					ft_draw_line(vec2_add(p0->x0, home->offset), vec2_add(p1->x0, home->offset), green, home->draw_surf);
					//fov = get_fov_points(p0, home, plr, i);
					// draw_rect_center(vec2_add(fov.left_point, home->offset), vec2(16, 16), home);
					// draw_rect_center(vec2_add(fov.right_point, home->offset), vec2(16, 16), home);
					ft_draw_line(vec2_add(fov.right_point, home->offset), vec2_add(fov.left_point, home->offset), 0xFF8000, home->draw_surf);
					draw_text(home, ft_itoa(hypotenuse(fov.left_point.x - fov.right_point.x, fov.left_point.y - fov.right_point.y)),
					vec2_add(vec2((fov.left_point.x - fov.right_point.x) / 2, (fov.left_point.y - fov.right_point.y) / 2), home->offset));
					//perspective_transformation(p0, p1, home, i);
					//draw_text(home, ft_itoa(fov.left_point.x), vec2(fov.left_point.x + 32, fov.left_point.y + 32));
					//draw_text(home, ft_ftoa(plr->angle, 5, '.'), vec2(50, 50));
					//draw_rect_center(fov.right_point, vec2(16, 16), home);
				}
			if (p0->next == NULL)
				break ;
			p0 = p0->next;
			}
		}
	//ft_draw_line(vec2_add(temp->x0, vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)), vec2_add(temp->next->x0, vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)), fuchsia, home->draw_surf);
	//draw_text(home, ft_ftoa(plr->angle, 5, '.'), vec2(50, 50));
	//draw_2d_fov(home, plr);
	// draw_text(home, ft_ftoa(plr->dir.x, 4, 1), vec2(plr->pos.x, plr->pos.y - 16));
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
