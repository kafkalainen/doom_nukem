/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:51:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 17:05:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_if_portal(t_wall *wall)
{
	if (wall->top.type >= 0 && wall->bot.type >= 0)
		return (true);
	else
		return (false);
}

t_bool	check_connection(t_wall *point, t_frame *frame)
{
	if (point->top.type == frame->old_idx)
		return (true);
	else
		return (false);
}

t_bool	check_if_already_been_in_this_sector(int cur_sector, int *sector_list,
		int nb_of_sectors)
{
	while (nb_of_sectors--)
	{
		if (sector_list[nb_of_sectors] == cur_sector)
			return (true);
	}
	return (false);
}

void	assign_booleans_for_fov(t_bool *res_left, t_bool *res_right,
		t_fov fov, t_wall *wall)
{
	*res_left = check_if_lseg_intersects(&wall->point, &wall->next->point,
			&fov.pos, &fov.left);
	*res_right = check_if_lseg_intersects(&wall->point, &wall->next->point,
			&fov.pos, &fov.right);
}

t_bool	check_if_facing_player(t_bool left, t_bool right, t_wall *wall,
		t_fov fov)
{
	if (!left && !right && point_inside_fov(fov.pos, fov.left, fov.right,
			wall->point) && point_inside_fov(fov.pos, fov.left, fov.right,
			wall->next->point))
		return (true);
	else
		return (false);
}
