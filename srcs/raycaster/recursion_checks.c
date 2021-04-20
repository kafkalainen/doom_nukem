/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:51:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 16:15:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void		continue_from_last_sector(t_point *start, t_ray_pt *fov, t_frame *frame)
{
	t_point *p0;

	p0 = start;
	if (frame->old_idx != -1)
	{
		while (p0)
		{
			if (check_connection(p0, frame))
			{
				fov->wall = p0->next;
				return ;
			}
			p0 = p0->next;
		}
	}
}

int		check_if_portal(t_point *p0)
{
	if (p0->idx >= 0)
		return (TRUE);
	else
		return (FALSE);
}

int				check_if_same_pt(int current_pxl, t_ray_pt *fov)
{

	if (current_pxl == 0
		&& get_distance(fov->l_pt, fov->r_pt) < 0.001)
		return (TRUE);
	else
		return (FALSE);
}

int		check_connection(t_point *point, t_frame *frame)
{
	return ((point->idx == frame->old_idx) ? TRUE : FALSE);
}
