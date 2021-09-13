/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_new_sector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:22:03 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/13 12:06:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../headers/doom_nukem.h"

static void	editor_initialize_sector_values(t_editor_sector *new,
			t_action *action)
{
	new->bbox.start = vec2(0, 0);
	new->bbox.end = vec2((0), (0));
	new->nb_of_walls = 0;
	new->tex_ceil = -surf0;
	new->tex_floor = -surf0;
	new->light.pos.x = 0;
	new->light.pos.y = 0;
	new->light.intensity = 0;
	new->light.is_linked = 0;
	new->light.state = 0;
	new->idx_sector = 0;
	new->centroid = vec2(0.0f, 0.0f);
	if (action->create_elev_button)
		new->is_elevator = 1;
	else
		new->is_elevator = 0;
	new->plot_line = NULL;
	new->walls = NULL;
	new->next = NULL;
}

void	editor_create_new_sector(t_editor_sector **head, t_action *action)
{
	t_editor_sector	*temp;
	t_editor_sector	*new;

	new = (t_editor_sector *)malloc(sizeof(t_editor_sector));
	if (!new)
		error_output("Memory allocation of sector failed\n");
	editor_initialize_sector_values(new, action);
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			new->idx_sector++;
			temp = temp->next;
		}
		new->idx_sector++;
		temp->next = new;
		new->next = NULL;
	}
	action->selected_sector = new->idx_sector;
}
