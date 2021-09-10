/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:40 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/10 13:20:40 by tmaarela         ###   ########.fr       */
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
