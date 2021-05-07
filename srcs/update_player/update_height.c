/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_height.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:01:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/07 13:51:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_height(t_xy *dir, float *z, t_point *to, int walls)
{
	t_intersection	sect;
	t_ray			plr;
	float			units_to_travel;
	t_height		height;

	plr.pos = vec2(0, 0);
	plr.dir = *dir;
	plr.cutpoint = vec2(-1, -1);
	while (walls)
	{
		calc_intersection(to, &plr, &sect);
		plr.cutpoint = line_intersection(&sect);
		if (plr.cutpoint.x != -1 && plr.cutpoint.y != -1)
			break ;
		to = to->next;
		walls--;
	}
	units_to_travel = vec2_mag(plr.cutpoint) / vec2_mag(*dir);
	interpolate_y(&height, plr.cutpoint, to, to->next);
	*z = *z + ((height.ground - *z) / units_to_travel);
}

int	check_height_diff(t_xy *dir, float *z, t_point *to, t_point *behind)
{
	t_intersection	sect;
	t_ray			plr;
	t_height		height_to;
	t_height		height_behind;

	plr.pos = vec2(0, 0);
	plr.dir = *dir;
	calc_intersection(to, &plr, &sect);
	plr.cutpoint = line_intersection(&sect);
	interpolate_y(&height_to, plr.cutpoint, to, to->next);
	calc_intersection(to, &plr, &sect);
	plr.cutpoint = line_intersection(&sect);
	interpolate_y(&height_behind, plr.cutpoint, behind, behind->next);
	height_to.ground = height_behind.ground - height_to.ground;
	if (height_to.ground - *z < 6)
	{
		*z = height_behind.ground;
		return (0);
	}
	else
	{
		ft_putstr("It's too high.");
		return (1);
	}
}
