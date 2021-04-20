/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:37:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/24 11:17:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

int		ft_draw_wall(t_xy left, t_xy right, t_frame *frame, int wall_len, int color, t_home *home, t_player *plr)
{
	float		screen_offset;
	float		wall_height_left;
	float		wall_height_right;
	float		step;
	float		z_step;
	float		angle_mult;
	int			pixels_drawn;

	pixels_drawn = 0;
	z_step = get_distance(plr->pos, left) / get_distance(plr->pos, right);
	screen_offset = SCREEN_WIDTH - frame->offset;
	wall_height_left = 480 / (fabs(left.x + left.y) * cosf(45 * DEG_TO_RAD)) * 20;
	wall_height_right = 480 / (fabs(right.x + right.y) * cosf(45 * DEG_TO_RAD)) * 20;
	step = (wall_height_left - wall_height_right) / wall_len;
	angle_mult = angle_offset(screen_offset, wall_len);
	while (pixels_drawn < wall_len)
	{
		ft_draw_line(
			vec2(screen_offset + pixels_drawn, plr->pitch - wall_height_left),
			vec2(screen_offset + pixels_drawn, plr->pitch + wall_height_left),
			color,
			frame->draw_surf);
		wall_height_left = wall_height_left - step + angle_mult;
		z_step -= wall_len * z_step;
		pixels_drawn++;
	}
	pixels_drawn++;
	draw_text(home, ft_itoa(wall_len), frame, vec2(screen_offset + wall_len * 0.5, 240));
	return (pixels_drawn);
}
