/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_from_next_point.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:33:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/19 14:09:05 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
void		continue_from_next_point(t_point *start, t_ray_fov *fov, t_frame *frame)
{
	fov->wall = fov->wall->next;
	fov->left_point = fov->wall->x0;
	fov->right_point = fov->wall->next->x0;
}
