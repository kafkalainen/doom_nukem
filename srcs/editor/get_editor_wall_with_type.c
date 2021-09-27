/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_editor_wall_with_type.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:50:22 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 10:29:10 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static t_bool	test_type(t_editor_walls *tmp, int type)
{
	if (tmp->type == type)
		return (true);
	else if (tmp->type == type + DOOR_INDEX)
		return (true);
	else if (tmp->type == type + CLEANING_INDEX)
		return (true);
	else if (tmp->type == type + ENGINEERING_INDEX)
		return (true);
	else if (tmp->type == type + MILITARY_INDEX)
		return (true);
	else if (tmp->type == type + SECRET_INDEX)
		return (true);
	else if (tmp->type == type + SMALL_WINDOW_INDEX)
		return (true);
	else if (tmp->type == type + LARGE_WINDOW_INDEX)
		return (true);
	else
		return (false);
}

t_editor_walls	*get_editor_wall_with_type(t_editor_walls **list,
				int nb_of_walls, int type)
{
	t_editor_walls	*tmp;

	tmp = *list;
	while (nb_of_walls--)
	{
		if (test_type(tmp, type))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
