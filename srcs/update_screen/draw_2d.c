/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:27:48 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/01 12:11:48 by jnivala          ###   ########.fr       */
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
	ft_draw_line(vec2_add(plr->pos, offset), vec2_add(vec2_add(plr->pos, vec2_mul(fov_left, 20)), offset), lightgreen, home->draw_surf);
	ft_draw_line(vec2_add(plr->pos, offset), vec2_add(vec2_add(plr->pos, vec2_mul(fov_right, 20)), offset), lightgreen, home->draw_surf);
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

void			draw_2d(t_home *home, t_player *plr)
{
	int i;
	t_point	*temp;
	t_point	*perkele;
	t_ray_fov	fov;

	i = 0;
	// while(i < 2)
	// {
	temp = home->sectors[i]->points;
		// while (temp)
		// {
			// if (temp->idx)
			// {
				// perkele = (temp->next == NULL) ? home->sectors[i]->points : temp->next;
				// fov = get_fov_points(temp, home, plr, i);
	// 			draw_rect_center(fov.left_point, vec2(16, 16), home);
	// 			draw_text(home, ft_itoa(fov.left_point.x), vec2(fov.left_point.x + 32, fov.left_point.y + 32));
	// 			draw_text(home, ft_ftoa(plr->angle, 5, '.'), vec2(50, 50));
	// 			draw_rect_center(fov.right_point, vec2(16, 16), home);
	// 			if (fov.left_point.x > 0)
	// 			{
	// 				if (fov.right_point.x > 0)
	// 					ft_draw_line(fov.left_point, fov.right_point, green, home->draw_surf);
	// 				else
	// 					ft_draw_line(fov.left_point, perkele->x0, green, home->draw_surf);
	// 			}
	// 		}
	// 		if (temp->next == NULL)
	// 			break ;
	// 		temp = temp->next;
	// 	}
	// 	i++;
	// }
	ft_draw_line(vec2_add(temp->x0, vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)), vec2_add(temp->next->x0, vec2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)), fuchsia, home->draw_surf);
	draw_text(home, ft_ftoa(plr->angle, 5, '.'), vec2(50, 50));
	draw_2d_fov(home, plr);
	// draw_text(home, ft_ftoa(plr->dir.x, 4, 1), vec2(plr->pos.x, plr->pos.y - 16));
}
