/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_node_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 08:01:34 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 08:32:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	copy_data_from_node(t_editor_walls *to, t_editor_walls *from)
{
	to->bbox = from->bbox;
	to->center_angle = from->center_angle;
	to->centroid_vec = from->centroid_vec;
	to->dist_from_center = from->dist_from_center;
	to->height = from->height;
	to->idx = from->idx;
	to->norm = from->norm;
	to->type = from->type;
	to->x0 = from->x0;
}

void	swap_node_data(t_editor_walls *data_0, t_editor_walls *data_1)
{
	t_editor_walls swap;

	if (!data_0 || !data_1)
		return ;
	copy_data_from_node(&swap, data_0);
	copy_data_from_node(data_0, data_1);
	copy_data_from_node(data_1, &swap);
}
