/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:51 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/10 12:48:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	free_walls(t_editor_walls **head, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int 			i;

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
	init_actions(&editor->action);
	editor->mouse_data.i_mbleft = 0;
	editor->mouse_data.i_mbright = 0;
	editor->mouse_data.selected = -1;
	editor->mouse_data.x = 0;
	editor->mouse_data.y = 0;
	editor->mouse_data.x_rel = 0;
	editor->mouse_data.y_rel = 0;
	editor->mapname = (unsigned char *)ft_strnew(sizeof(unsigned char) * (ft_strlen((const char *)path) + 1));
	editor->mapname = (unsigned char *)ft_strcpy((char *)editor->mapname, (const char *)path);
	editor->action.map_name_set = 1;
}

int		editor_parse_map_name(t_editor *editor, ssize_t size, unsigned char *buf, unsigned int **pos)
{
	size_t	len;

	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	len = get_next_breaker(buf + **pos);
	editor->linked_mapname = (unsigned char *)ft_strndup((const char *)buf + **pos, len - 1);
	return (0);
}

int		editor_get_map_header(unsigned int *pos, unsigned char *buf, t_editor *editor, ssize_t size)
{
	int	linked;
	int	nbr_of_sectors;

	nbr_of_sectors = 0;
	linked = 0;
	if (get_next_int_value(&nbr_of_sectors, buf, &pos, size))
		return (-1);
	if (get_next_int_value(&editor->end_sector, buf, &pos, size))
		return (-1);
	if (nbr_of_sectors <= 0 || editor->end_sector <= 0)
		return (-1);
	if (get_next_int_value(&linked, buf, &pos, size))
		return (-1);
	if (linked)
	{
		if (editor_parse_map_name(editor, size, buf, &pos))
			return (-1);
	}
	return (nbr_of_sectors);
}

static int	editor_get_player_position(unsigned int *pos, unsigned char *buf,
			t_plr_pos *plr, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->x = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->z = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->sector = ft_atoi((const char *)buf + *pos);
	return (0);
}

int	editor_parse_vertex_data(t_editor_sector *new, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	new->idx_sector = ft_atoi((const char *)buf + *pos);
	if (get_next_int_value(&new->nb_of_walls, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->tex_floor, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->tex_ceil, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->is_elevator, buf, &pos, size))
		return (1);
	*pos += get_next_breaker(buf + *pos);
	if (*pos > (unsigned int)size)
		return (1);
	return (0);
}

t_editor_walls	*editor_new_point(t_point_data *data)
{
	t_editor_walls	*new;

	new = (t_editor_walls *)malloc(sizeof(t_editor_walls));
	if (new != NULL)
	{
		new->x0.x = data->x;
		new->x0.y = data->y;
		new->type = data->idx;
		new->bbox.start = vec2(new->x0.x - 0.2f, new->x0.y + 0.2f);
		new->bbox.end = vec2((new->x0.x + 0.2f), (new->x0.y - 0.2f));
		new->height.ground = data->ground;
		new->height.ceiling = data->ceiling;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

int	editor_parse_coordinates(t_point_data *data,
	unsigned int ***pos, unsigned char **buf, ssize_t size)
{
	***pos += 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->x = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->y = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->idx = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->ground = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos) + 1;
	if (***pos > (unsigned int)size)
		return (1);
	data->ceiling = ft_atoi((const char *)*buf + ***pos);
	***pos += get_next_breaker(*buf + ***pos);
	if (***pos > (unsigned int)size)
		return (1);
	return (0);
}

int	editor_add_points(t_editor_sector *sector,
	unsigned char *buf, unsigned int **pos, ssize_t size)
{
	int				i;
	t_point_data	data;
	t_editor_walls	*wall;

	i = 0;
	if (sector == NULL)
		return (1);
	while (i < sector->nb_of_walls)
	{
		if (editor_parse_coordinates(&data, &pos, &buf, size))
			return (1);
		wall = editor_new_point(&data);
		if (!wall)
			return (1);
		add_point_end(&sector->walls, wall);
		i++;
	}
	close_editor_wall_list(&sector->walls);
	assign_sector_bbox(sector);
	return (0);
}

int	editor_parse_light_data(t_editor_sector *new, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	if (get_next_int_value(&new->light.pos.x, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->light.pos.y, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->light.intensity,
			buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->light.state, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new->light.is_linked, buf, &pos, size))
		return (1);
	return (0);
}

char	*editor_get_next_string(unsigned char *buf,
			unsigned int **pos, ssize_t size)
{
	ssize_t	len;
	char	*str;

	str = NULL;
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (NULL);
	len = get_next_breaker(buf + **pos);
	str = ft_strndup((const char *)buf + **pos, len);
	return (str);
}

int	editor_parse_story_data(t_editor_sector *new, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	int	i;
	int	lines;

	i = 0;
	if (get_next_int_value(&lines, buf, &pos, size))
		return (1);
	if (lines == 0)
		return (0);
	while (i < lines)
	{
		if (new->sector_plot == NULL)
			new->sector_plot = (unsigned char *)editor_get_next_string(buf, &pos, size);
		else
			new->sector_plot = (unsigned char *)ft_strjoin_freeable((char *)new->sector_plot, editor_get_next_string(buf, &pos, size), 1, 1);
		if (new->sector_plot == NULL)
			return (1);
		i++;
	}
	return (0);
}

int	editor_get_sector_data(unsigned char *buf, unsigned int *pos,
	ssize_t size, t_editor_sector **head)
{
	t_editor_sector	*temp;
	t_editor_sector	*new;

	new = (t_editor_sector *)malloc(sizeof(t_editor_sector));
	if (!new)
		return (1);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
	if (!buf)
		return (1);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size
		|| !ft_strnequ((const char *)(buf + *pos), "sector", 6))
		return (1);
	*pos += 6;
	if (*pos > (unsigned int)size)
		return (1);
	new->walls = NULL;
	new->sector_plot = NULL;
	if (editor_parse_vertex_data(new, buf, pos, size))
		return (1);
	if (editor_add_points(new, buf, &pos, size))
		return (1);
	if (editor_parse_light_data(new, buf, pos, size))
		return (1);
	if (editor_parse_story_data(new, buf, pos, size))
		return (1);
	return (0);
}

int		editor_parse_sector_data(t_editor *editor, unsigned char *buf, ssize_t size)
{
	unsigned int	pos;
	int				i;
	int				nbr_of_sectors;

	i = 0;
	pos = 0;
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_sectors");
	if (!buf )
		return (1);
	nbr_of_sectors = editor_get_map_header(&pos, buf, editor, size);
	if (nbr_of_sectors < 0)
		return (1);
	if (editor_get_player_position(&pos, buf, &editor->plr, size))
		return (1);
	while (i < nbr_of_sectors)
	{
		if (editor_get_sector_data(buf, &pos, size, &editor->sector_list))
			error_output("Something went wrong while reading sector data\n");
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_entities", 20))
		error_output("ERROR: Invalid data ender for entities.");
	return (0);
}

int	editor_check_entity_data_header(unsigned char **buf, unsigned int *pos, ssize_t size)
{
	int	i;

	i = 0;
	*buf = (unsigned char *)ft_strstr((const char *)*buf,
			"doom_nukem_entities");
	if (!*buf)
		error_output("ERROR: Invalid data buffer for entity data.");
	*pos += get_next_breaker(*buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		error_output("ERROR: Invalid buffer length.");
	i = ft_atoi((const char *)*buf + *pos);
	return (i);
}

Uint32	editor_parse_coordinate(t_editor_xyz *coord, unsigned char *buf,
				unsigned int **pos, ssize_t size)
{
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->x = ft_atoi((const char *)buf + **pos);
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->z = ft_atoi((const char *)buf + **pos);
	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	coord->y = ft_atoi((const char *)buf + **pos);
	return (0);
}

int	editor_get_entity_data(unsigned char *buf, t_entity_list *entity,
		unsigned int *pos, ssize_t size)
{
	if (get_next_int_value(&entity->entity_type, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->sector_idx, buf, &pos, size))
		return (1);
	if (editor_parse_coordinate(&entity->pos, buf, &pos, size))
		return (1);
	if (editor_parse_coordinate(&entity->dir, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_static, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_active, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_revealed, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->state, buf, &pos, size))
		return (1);
	if (get_next_int_value(&entity->is_linked, buf, &pos, size))
		return (1);
	entity->bbox.start = vec2(entity->pos.x - 0.2f, entity->pos.z + 0.2f);
	entity->bbox.end = vec2(entity->pos.x + 0.2f, entity->pos.z - 0.2f);
	return (0);
}

t_entity_list	*new_entity(t_entity_list **head)
{
	t_entity_list	*temp;
	t_entity_list	*new;

	new = (t_entity_list *)malloc(sizeof(t_entity_list));
	if (!new)
		error_output("Memory allocation of new entity failed\n");
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
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
	// if (pos > (unsigned int)size
	// 	|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_textures", 20))
	// 	error_output("ERROR: Invalid data ender for entities.");
	return (0);
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
	doom_open(&fd, (const char **)&path, TEXT_ONLY, 0644);
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
