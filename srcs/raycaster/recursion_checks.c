/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:51:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/07 11:18:46 by jnivala          ###   ########.fr       */
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

int	check_if_portal(t_wall *wall)
{
	if (wall->top.idx >= 0)
		return (TRUE);
	else
		return (FALSE);
}

// int	check_if_same_pt(int *current_pxl, t_ray_pt *fov)
// {
// 	if (*current_pxl < 1 && vec2_eucl_dist(fov->l_pt, fov->r_pt) < 0.001)
// 		return (TRUE);
// 	else
// 	{
// 		if (*current_pxl == 0)
// 		{
// 			*current_pxl = 1;
// 		}
// 		return (FALSE);
// 	}
// }

int	check_connection(t_wall *point, t_frame *frame)
{
	if (point->top.idx == frame->old_idx)
		return (TRUE);
	else
		return (FALSE);
}

Uint32	check_if_open_portal(t_wall *wall)
{
	if (wall->top.idx >= 0)
		return (TRUE);
	else
		return (FALSE);
}
