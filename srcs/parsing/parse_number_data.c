/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:23:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/28 11:27:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	parse_vertex_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	new_sector->idx_sector = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->nb_of_walls = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->tex_floor = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->tex_ceil = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos);
	if (*pos > (unsigned int)size)
		return (1);
	return (0);
}

int	parse_light_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->lights.light_src.x = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->lights.light_src.z = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->lights.diffuse_power = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->lights.state = ft_atoi((const char *)buf + *pos);
	new_sector->lights.light_src.y = 0.0f;
	new_sector->lights.light_src.w = 1.0f;
	return (0);
}

int	parse_coordinates(t_point_data *data,
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

int	parse_story_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->nb_of_msgs = ft_atoi((const char *)buf + *pos);
	if (new_sector->nb_of_msgs)
		new_sector->story = (char **)malloc(sizeof(char *)
			* (new_sector->nb_of_msgs + 1));
	else
		new_sector->story = NULL;
	if (new_sector->nb_of_msgs && !new_sector->story)
		return (1);
	while (i < new_sector->nb_of_msgs)
	{
		*pos += get_next_breaker(buf + *pos) + 1;
		len = get_next_breaker(buf + *pos);
		new_sector->story[i] = ft_strndup((const char *)buf + *pos, len);
		i++;
	}
	new_sector->cur_msg = 0;
	return (0);
}

int	parse_map_name(t_home *home, ssize_t size, unsigned char *buf,
	unsigned int **pos)
{
	char	*temp;
	size_t	len;

	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	len = get_next_breaker(buf + **pos);
	ft_strdel(&home->chosen_map);
	temp = ft_strndup((const char *)buf + **pos, len - 1);
	home->chosen_map = ft_strjoin("map_files/", temp);
	ft_strdel(&temp);
	return (0);
}
