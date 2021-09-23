/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_editor_wall_with_type.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:50:22 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 16:02:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_walls	*get_editor_wall_with_type(t_editor_walls **list,
				int nb_of_walls, int type)
{
	t_editor_walls	*tmp;

	tmp = *list;
	while (nb_of_walls--)
	{
		if (tmp->type == type)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
