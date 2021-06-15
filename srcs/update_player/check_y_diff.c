/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_y_diff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:01:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/15 16:08:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		check_y_diff(t_player *plr, t_xyz *test_pos, t_sector *to)
{
	*test_pos = check_y(to, plr, *test_pos);
	if (check_distance_to_ceiling(to, test_pos))
	{
		ft_putstr("It's too low.");
		return (1);
	}
	if (test_pos->y - plr->pos.y < plr->height)
		return (0);
	else
	{
		ft_putstr("It's too high.");
		return (1);
	}
}
