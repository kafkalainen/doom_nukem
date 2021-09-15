/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_delete_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:16:14 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/15 15:40:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_remove_last_wall(t_editor_sector *sector_list)
{
	t_editor_walls *temp;

	temp = sector_list->walls;
	if (sector_list->nb_of_walls == 1)
		return ;
	remove_last_point(&temp, &sector_list->nb_of_walls);
}
