/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_sources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:39:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/01 13:52:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	calc_light_sources(t_home *home)
{
	Uint32	i;

	i = 0;
	while (i < home->nbr_of_sectors)
	{
		home->sectors[i]->lights.light_src.y
			= calc_distance_to_ceiling(home->sectors[i],
				&home->sectors[i]->lights.light_src);
		if (home->sectors[i]->lights.light_src.y > 0.5f)
			home->sectors[i]->lights.light_src.y -= 0.5f;
		i++;
	}
}
