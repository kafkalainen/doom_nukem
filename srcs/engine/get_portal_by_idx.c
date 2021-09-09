/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_portal_by_idx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:28:18 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_wall	*get_portal_by_idx(int idx, t_sector *sector)
{
	t_wall			*temp;
	unsigned int	i;

	if (sector == NULL)
		return (NULL);
	i = 0;
	temp = sector->walls;
	while (i < sector->nb_of_walls)
	{
		if (temp->top.type == idx || temp->top.type == idx + DOOR_INDEX)
			return (temp);
		temp = temp->next;
		i++;
	}
	return (NULL);
}
