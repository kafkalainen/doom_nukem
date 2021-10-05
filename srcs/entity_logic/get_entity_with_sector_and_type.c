/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entity_with_sector_and_type.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:18:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/05 10:29:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity	*get_entity_with_sector_and_type(int sector_idx, t_uint type,
			t_home *home)
{
	t_uint	i;

	i = 0;
	while (i < home->nbr_of_entities)
	{
		if (home->entity_pool[i]->sector_idx == sector_idx
			&& home->entity_pool[i]->type == type)
			return (home->entity_pool[i]);
		i++;
	}
	return (NULL);
}
