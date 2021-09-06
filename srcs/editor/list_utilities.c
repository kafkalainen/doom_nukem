/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:40:49 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/13 14:21:29 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_sector_list *find_sector(t_sector_list **sector, int s_idx, int w_idx)
{	
	t_sector_list *temp;

	temp = *sector;
	while (temp && temp->idx_sector != s_idx)
		temp = temp->next;
	if (temp== NULL)
		return (NULL);
	if (w_idx != -1)
	{
		while (temp && temp->walls && temp->walls->idx != w_idx)
			temp->walls = temp->walls->next;
	}
	return (temp);
}
