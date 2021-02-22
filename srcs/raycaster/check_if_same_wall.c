/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:15:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 14:15:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int				check_if_same_wall(t_xy a, t_xy b, t_xy right_point)
{
	if (a.x == b.x && a.y == b.y)
	{
		if (right_point.x != -1 && right_point.y != -1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
