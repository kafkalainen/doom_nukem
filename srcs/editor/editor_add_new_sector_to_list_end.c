/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_add_new_sector_to_list_end.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:36:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/13 11:55:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_editor_sector	*editor_add_new_sector_to_list_end(t_editor_sector **head)
{
	t_editor_sector	*new_sector;
	t_editor_sector	*temp;

	new_sector = (t_editor_sector *)malloc(sizeof(t_editor_sector));
	if (!new_sector)
		return (NULL);
	new_sector->next = NULL;
	if (*head == NULL)
		*head = new_sector;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_sector;
		new_sector->next = NULL;
	}
	return (new_sector);
}
