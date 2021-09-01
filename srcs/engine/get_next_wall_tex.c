/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wall_tex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:19:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/10 11:38:26 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_next_wall_tex(t_wall **current_head, int nbr_of_walls)
{
	t_wall	*temp;

	temp = *current_head;
	while (nbr_of_walls)
	{
		if (temp->top.idx < 0)
			return (temp->top.idx);
		temp = temp->next;
		nbr_of_walls--;
	}
	return (-1);
}
