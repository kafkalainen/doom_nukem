/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_sectors_for_intersecting_lines.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:20:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/10 15:28:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	check_all_sectors_for_intersecting_lines(t_editor_sector **head,
		t_screen_xy p0, t_screen_xy p1)
{
	t_editor_sector	*temp;
	t_editor_sector	*original_head;

	temp = *head;
	original_head = *head;
	while (temp)
	{
		if (check_for_intersecting_lines(temp, p0, p1))
			return (true);
		temp = temp->next;
	}
	temp = original_head;
	return (false);
}
