/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:52:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 09:17:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_fps(t_buffer *buffer, int nb_fps)
{
	char			*fps;
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	fps = ft_itoa(nb_fps);
	mod.len = ft_strlen(fps);
	if (!fps)
		return ;
	ft_str_pxl(buffer, vec2(SCREEN_WIDTH * 0.5 - 15, 0), fps, mod);
	free(fps);
}

static int	compass_direction(float angle)
{
	if ((angle <= NW && angle >= 0) || (angle <= N && angle > NE))
		return (0);
	else if (angle <= SW && angle > NW)
		return (1);
	else if (angle <= SE && angle > SW)
		return (2);
	else if (angle <= NE && angle > SE)
		return (3);
	else
		return (4);
}

void	draw_compass_direction(t_buffer *buffer, t_xy *dir)
{
	t_plx_modifier	mod;
	t_xy			loc;
	float			angle;
	const char		*points[] = {"::North::", "::West::", "::South::",
								"::East::", "::No dir::"};
	const int		tab[] = {9, 8, 9, 8, 10};

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 0;
	loc = vec2(0.0f, buffer->height * 0.05f);
	angle = -vec2_ang(*dir, (t_xy){0.0f, 1.0f, 1.0f});
	if (angle < 0.0f)
		angle = TWO_PI + angle;
	mod.len = tab[compass_direction(angle)];
	loc.x = center_text_x_axis(0, buffer->width, mod.size, mod.len);
	ft_str_pxl(buffer, loc, (char *)points[compass_direction(angle)], mod);
}

void	draw_info(t_buffer *buffer)
{
	t_plx_modifier	mod;

	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	mod.len = 100;
	ft_str_pxl(buffer, vec2(10, 280), "1 2 3 4 to select item", mod);
	ft_str_pxl(buffer, vec2(10, 300), "f to use item", mod);
	ft_str_pxl(buffer, vec2(10, 320), "c to close info", mod);
	ft_str_pxl(buffer, vec2(10, 340), "z to pause music", mod);
	ft_str_pxl(buffer, vec2(10, 360), "wasd, rotate with q and e.",
		mod);
	ft_str_pxl(buffer, vec2(10, 380), "free mouse with m", mod);
	ft_str_pxl(buffer, vec2(10, 400), "shoot with left mouse", mod);
	ft_str_pxl(buffer, vec2(10, 420), "fly with right mouse", mod);
	ft_str_pxl(buffer, vec2(10, 440), "jump with space", mod);
	ft_str_pxl(buffer, vec2(10, 460), "crouch with left ctrl", mod);
}
