/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:26:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/20 16:37:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	setup_frame(t_fov *new_fov, t_fov *fov, t_wall *wall)
{
	new_fov->pos = fov->pos;
	new_fov->left = fov->left;
	new_fov->right = fov->right;
	new_fov->cur_sector = wall->top.type;
}
