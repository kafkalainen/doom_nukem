/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_previous_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:18:08 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/24 14:26:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_walls	*get_previous_wall(t_editor_walls *wall,
				t_editor_sector *sector)
{
	t_editor_walls	*temp;
	int				nb_of_walls;

	temp = sector->walls;
	nb_of_walls = sector->nb_of_walls;
	while (nb_of_walls--)
	{
		if (temp->next->idx == wall->idx)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
