/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_towards_centroid.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 09:28:22 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 10:20:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	translate_towards_centroid(t_editor_sector *sector)
{
	int				i;
	t_editor_walls	*walls;

	i = 0;
	walls = sector->walls;
	while (i < sector->nb_of_walls)
	{
		walls->bbox.start = vec2_add(walls->bbox.start,
				vec2_mul(walls->centroid_vec, -0.28f));
		walls->bbox.end = vec2_add(walls->bbox.end,
				vec2_mul(walls->centroid_vec, -0.28f));
		walls = walls->next;
		i++;
	}
}
