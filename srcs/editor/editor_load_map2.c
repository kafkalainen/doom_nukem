/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/07 11:40:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	free_walls(t_editor_walls **head, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				i;

	i = 0;
	while (*head != NULL && i < nbr_of_walls)
	{
		temp = *head;
		*head = temp->next;
		free(temp);
		temp = NULL;
		i++;
	}
}

void	editor_free_all_sectors(t_editor_sector **head)
{
	t_editor_sector	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = temp->next;
		free_walls(&temp->walls, temp->nb_of_walls);
		free(temp);
		temp = NULL;
	}
}

void	load_map_names_to_memory(t_editor *editor)
{
	editor->action.nbr_of_maps = 0;
	load_map_names(&editor->map_names, &editor->action.nbr_of_maps);
	editor->action.option = 0;
	editor->action.start = 0;
	editor->action.end = 0;
	if ((editor->action.nbr_of_maps - 8) > 0)
		editor->action.end = 7;
	else
		editor->action.end = editor->action.nbr_of_maps - 1;
}

void	reload_editor_with_defaults(t_editor *editor, char *path)
{
	free_all_entities(&editor->entity_list);
	editor_free_all_sectors(&editor->sector_list);
	editor->entity_list = NULL;
	editor->sector_list = NULL;
	if (editor->mapname)
		free(editor->mapname);
	if (editor->linked_mapname)
		free(editor->linked_mapname);
	editor->mapname = NULL;
	editor->linked_mapname = NULL;
	initialize_actions(&editor->action);
	editor->mouse_data.i_mbleft = 0;
	editor->mouse_data.i_mbright = 0;
	editor->mouse_data.selected = -1;
	editor->mouse_data.x = 0;
	editor->mouse_data.y = 0;
	editor->mapname = (unsigned char *)ft_strnew(sizeof(unsigned char)
			* (ft_strlen((const char *)path) + 1));
	editor->mapname = (unsigned char *)ft_strcpy((char *)editor->mapname,
			(const char *)path);
	editor->action.map_name_set = 1;
}

int	editor_parse_map_name(t_editor *editor, ssize_t size,
		unsigned char *buf, unsigned int **pos)
{
	size_t	len;

	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	len = get_next_breaker(buf + **pos);
	editor->linked_mapname
		= (unsigned char *)ft_strndup((const char *)buf + **pos, len - 1);
	return (0);
}
