/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_portal_by_idx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:28:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/05 13:33:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_point	*get_portal_by_idx(int idx, t_sector *sector)
{
	t_point			*temp;
	unsigned int	i;

	if (sector == NULL)
		return (NULL);
	i = 0;
	temp = sector->points;
	while (i < sector->nb_of_walls)
	{
		if (temp->idx == idx)
			return (temp);
		temp = temp->next;
		i++;
	}
	return (NULL);
}
