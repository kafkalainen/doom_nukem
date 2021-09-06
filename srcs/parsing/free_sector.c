/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:05:23 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/04 11:40:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	free_points(t_wall **head, unsigned int nbr_of_walls)
{
	t_wall	*item;

	while (nbr_of_walls--)
	{
		item = *head;
		*head = item->next;
		free(item);
		item = NULL;
	}
	return (true);
}

void	free_sectors(t_home *home)
{
	unsigned int	i;

	i = 0;
	if (home == NULL)
		return ;
	if (home->skybox.face)
		free(home->skybox.face);
	while (i < home->nbr_of_sectors)
	{
		free_points(&home->sectors[i]->walls, home->sectors[i]->nb_of_walls);
		free_surfaces(&home->sectors[i]->ground, home->sectors[i]->nb_of_ceil);
		free_surfaces(&home->sectors[i]->ceiling,
			home->sectors[i]->nb_of_ground);
		free_story(&home->sectors[i]->story, home->sectors[i]->nb_of_msgs);
		free(home->sectors[i]);
		home->sectors[i] = NULL;
		i++;
	}
	free(home->sectors);
	home->sectors = NULL;
}

void	free_sectors_n(t_home *home, size_t n)
{
	size_t	i;

	i = 0;
	if (home == NULL)
		return ;
	if (home->skybox.face)
		free(home->skybox.face);
	while (i < n)
	{
		if (i + 1 < n)
		{
			free_points(&home->sectors[i]->walls,
				home->sectors[i]->nb_of_walls);
		}
		free(home->sectors[i]);
		home->sectors[i] = NULL;
		i++;
	}
	free(home->sectors);
	home->sectors = NULL;
}

t_sector	*free_sector(t_sector **sector)
{
	if (*sector == NULL)
		return (NULL);
	free(*sector);
	*sector = NULL;
	return (*sector);
}
