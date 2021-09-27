/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:19:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 14:19:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_next_wall_tex(t_wall **current_head, int nbr_of_walls)
{
	t_wall	*temp;

	temp = *current_head;
	while (nbr_of_walls)
	{
		if (temp->top.type < 0 && temp->top.type != -door
			&& temp->top.type != -small_window
			&& temp->top.type != -large_window)
			return (temp->top.type);
		temp = temp->next;
		nbr_of_walls--;
	}
	return (-wall0);
}
