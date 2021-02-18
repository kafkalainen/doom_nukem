/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_from_next_point.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 08:33:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/08 10:09:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"
void		continue_from_next_point(t_point *start, t_ray_fov *fov, t_frame *frame)
{
	fov->left_wall = fov->left_wall->next;
	fov->left_point = fov->left_wall->x0;
	fov->right_point = fov->left_wall->next->x0;
}
