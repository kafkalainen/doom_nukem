/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_editor_sector_with_idx.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:46:30 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 09:47:39 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*get_editor_sector_with_idx(t_editor_sector **list, int idx)
{
	t_editor_sector	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->idx_sector == idx)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
