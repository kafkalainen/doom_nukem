/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_from_last_sector.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:01:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/19 14:08:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

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
