/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:51:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:39:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	continue_from_last_sector(t_wall *start, t_ray_pt *fov, t_frame *frame)
{
	t_wall	*temp;

	temp = start;
	if (frame->old_idx != old_sector)
	{
		while (temp)
		{
			if (check_connection(temp, frame))
			{
				fov->wall = temp->next;
				return ;
			}
			temp = temp->next;
		}
	}
}

t_bool	check_if_portal(t_wall *wall)
{
	if (wall->top.type >= 0 && wall->bottom.type >= 0)
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
