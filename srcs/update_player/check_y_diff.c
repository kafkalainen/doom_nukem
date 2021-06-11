/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_y_diff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:01:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 16:23:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int		check_y_diff(t_xyz *current_pos, t_xyz *test_pos, t_sector *to,
	float cur_height)
{
	t_xyz	new_height;

	new_height = check_y(to, *test_pos, cur_height);
	if (new_height.y - current_pos->y < cur_height)
		return (0);
	else
	{
		ft_putstr("It's too high.");
		return (1);
	}
}
