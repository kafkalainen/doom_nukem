/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/17 17:32:00 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_entity_list	*new_entity(t_entity_list **head)
{
	t_entity_list	*temp;
	t_entity_list	*new;

	new = (t_entity_list *)malloc(sizeof(t_entity_list));
	if (!new)
		error_output("Memory allocation of new entity failed\n");
	new->next = NULL;
	new->entity_idx = 0;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			new->entity_idx++;
			temp = temp->next;
		}
		new->entity_idx++;
		temp->next = new;
		new->next = NULL;
	}
	return (new);
}

int	editor_parse_entity_data(t_editor *editor, unsigned char *buf, ssize_t size)
{
	unsigned int	pos;
	unsigned int	i;
	unsigned int	nbr_of_entities;
	t_entity_list	*temp;

	i = 0;
	pos = 0;
	nbr_of_entities = editor_check_entity_data_header(&buf, &pos, size);
	while (i < nbr_of_entities)
	{
		temp = new_entity(&editor->entity_list);
		if (editor_get_entity_data(buf, temp, &pos, size))
			return (1);
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_textures", 20))
		error_output("ERROR: Invalid data ender for entities.");
	return (0);
}

static	void	set_end_sector_coordinates(t_plr_pos *end,
	t_editor_sector **head)
{
	t_editor_sector	*temp;

	temp = get_editor_sector_with_idx(head, end->sector);
	if (!temp)
		error_output("ERROR: Invalid end sector.\n");
	end->x = (int)temp->centroid.x;
	end->z = (int)temp->centroid.y;
}

void	read_map_data(t_editor *editor, unsigned char *buf, ssize_t size)
{
	int	ret;

	ret = editor_parse_sector_data(editor, buf, size);
	if (ret)
		error_output("Something went horribly wrong\n");
	editor->action.player_start_assigned = 1;
	ret = editor_parse_entity_data(editor, buf, size);
	if (ret)
		error_output("something went horribly wrong\n");
	set_end_sector_coordinates(&editor->end_sector, &editor->sector_list);
}

void	editor_load_map(t_editor *editor)
{
	int				fd;
	unsigned char	*buf;
	ssize_t			size;
	char			*path;

	path = NULL;
	path = ft_strjoin("./map_files/", editor->map_names[editor->action.option]);
	buf = (unsigned char *)malloc(sizeof(unsigned char) * (MAX_SIZE + 1));
	if (!buf)
		error_output("ERROR: Failed allocate memory for the map.");
	doom_open(&fd, (const char **)&path, READ_ONLY, 0644);
	if (fd < 0)
		error_output("ERROR: Failed to open map");
	else
	{
		doom_read(&size, &fd, (void **)&buf, MAX_SIZE);
		if (size <= 0 || size == MAX_SIZE || doom_close(&fd) == -1)
			read_error_output("ERROR: Failed to read map.", &buf);
		buf[size] = '\0';
		verify_hash(buf, size);
		reload_editor_with_defaults(editor, path);
		read_map_data(editor, buf, size);
		free(path);
		free(buf);
	}
}
