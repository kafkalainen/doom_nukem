/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_non_convex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 09:05:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 17:17:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_xy	vec2_screen_dec(t_screen_xy a, t_screen_xy b)
{
	return (vec2_dec((t_xy){a.x, a.y}, (t_xy){b.x, b.y}));
}

int	check_if_non_convex(t_sector_list *sector)
{
	int				i;
	t_xy			dxy_1;
	t_xy			dxy_2;
	t_editor_walls	*temp;
	int				sign;

	i = 0;
	temp = sector->walls;
	if (sector->nb_of_walls == 3)
		return (0);
	while (i < sector->nb_of_walls)
	{
		dxy_1 = vec2_screen_dec(temp->next->x0, temp->x0);
		dxy_2 = vec2_screen_dec(temp->next->next->x0, temp->next->x0);
		if (i != 0 && is_negative(vec2_cross(dxy_1, dxy_2)) != sign)
			return (1);
		else
			sign = is_negative(vec2_cross(dxy_1, dxy_2));
		temp = temp->next;
		i++;
	}
	return (0);
}
