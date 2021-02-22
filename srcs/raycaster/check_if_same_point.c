/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_same_point.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:40:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 10:34:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int				check_if_same_point(int current_pxl, t_ray_fov *fov)
{

	if (current_pxl == 0
		&& get_distance(fov->left_point, fov->right_point) < 0.001)
		return (TRUE);
	else
		return (FALSE);
}
