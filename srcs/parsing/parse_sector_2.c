/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:29:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 13:33:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	add_to_middle(t_wall **current_point, t_wall *new)
{
	t_wall	*temp;

	if (new == NULL)
		return ;
	if (*current_point == NULL)
	{
		*current_point = new;
	}
	else
	{
		temp = (*current_point)->next;
		(*current_point)->next = new;
		new->next = temp;
	}
}
