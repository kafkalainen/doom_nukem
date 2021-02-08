/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_from_last_sector.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:01:11 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/08 10:58:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../doom_nukem.h"

void		continue_from_last_sector(t_point *start, t_ray_fov *fov, t_frame *frame)
{
	t_point *p0;

	p0 = start;
	if (frame->old_idx != -1)
	{
		while (p0)
		{
			if (check_connection(p0, frame))
			{
				fov->left_wall = p0;
				break ;
			}
			p0 = p0->next;
		}
	}
}
