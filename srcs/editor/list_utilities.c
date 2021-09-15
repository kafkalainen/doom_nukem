/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 19:27:13 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*find_sector(t_editor_sector **sector, int s_idx, int w_idx)
{
	t_editor_sector	*temp;

	temp = *sector;
	while (temp && temp->idx_sector != s_idx)
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	if (w_idx != -1)
	{
		while (temp && temp->walls && temp->walls->idx != w_idx)
			temp->walls = temp->walls->next;
	}
	return (temp);
}
