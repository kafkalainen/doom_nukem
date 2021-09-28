/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/28 10:18:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

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
	sector->centroid = editor_calculate_centroid(sector);
	editor_sort_wall_vertices(sector);
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

t_uchar	*editor_get_new_string(unsigned char *buf,
			unsigned int **pos, ssize_t size, int lines)
{
	t_uchar	*str;

	str = (t_uchar *)editor_get_next_string(buf, pos, size);
	if (lines > 1)
		return ((t_uchar *)ft_strjoin_newline((char **)&str));
	else
		return (str);
}

int	editor_parse_story_data(t_editor_sector *sec, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	int	lines;

	if (get_next_int_value(&lines, buf, &pos, size))
		return (1);
	if (lines == 0)
		return (0);
	while (lines)
	{
		if (sec->plot_line == NULL)
			sec->plot_line = editor_get_new_string(buf, &pos, size, lines);
		else
		{
			sec->plot_line = (t_uchar *)ft_strjoin_freeable(
					(char *)sec->plot_line,
					editor_get_next_string(buf, &pos, size), 1, 1);
			if (lines - 1)
				sec->plot_line = ft_strjoin_newline((char **)&sec->plot_line);
		}
		if (sec->plot_line == NULL)
			return (1);
		lines--;
	}
	return (0);
}
