/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_surfaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:56:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 08:20:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_surface	*new_surface(t_wall *data, t_xyz *start, int idx, char choice)
{
	t_surface	*surface;

	surface = (t_surface *)malloc(sizeof(*surface));
	if (surface != NULL)
	{
		surface->tri.p[0] = *start;
		if (choice == 'g')
		{
			surface->tri.p[1] = data->bottom.p[0];
			surface->tri.p[2] = data->next->bottom.p[0];
		}
		else
		{
			surface->tri.p[2] = data->top.p[1];
			surface->tri.p[1] = data->next->top.p[1];
		}
		surface->tri.idx = idx;
		surface->next = NULL;
	}
	else
	{
		free(surface);
		surface = NULL;
	}
	return (surface);
}

void	add_surface(t_surface **point, t_surface *new)
{
	t_surface	*temp;

	if (new == NULL)
		return ;
	if (*point == NULL)
	{
		*point = new;
	}
	else
	{
		temp = *point;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

void	close_surface_list(t_surface **head)
{
	t_surface	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

int	free_surfaces(t_surface **head, unsigned int nbr_of_surfaces)
{
	t_surface	*item;

	while (nbr_of_surfaces--)
	{
		item = *head;
		*head = item->next;
		free(item);
		item = NULL;
	}
	return (1);
}
