/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:23:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/06 16:45:35 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	parse_vertex_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	new_sector->idx_sector = ft_atoi((const char *)buf + *pos);
	if (get_next_uint_value(&new_sector->nb_of_walls, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new_sector->tex_floor, buf, &pos, size))
		return (1);
	if (get_next_int_value(&new_sector->tex_ceil, buf, &pos, size))
		return (1);
	if (get_next_uint_value(&new_sector->is_lift, buf, &pos, size))
		return (1);
	*pos += get_next_breaker(buf + *pos);
	if (*pos > (unsigned int)size)
		return (1);
	new_sector->moving_until = 0;
	new_sector->lift_dir = lower;
	return (0);
}

int	parse_light_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos, ssize_t size)
{
	if (get_next_float_value(&new_sector->lights.light_src.x, buf, &pos, size))
		return (1);
	if (get_next_float_value(&new_sector->lights.light_src.z, buf, &pos, size))
		return (1);
	if (get_next_float_value(&new_sector->lights.diffuse_power,
			buf, &pos, size))
		return (1);
	if (get_next_uint_value(&new_sector->lights.state, buf, &pos, size))
		return (1);
	if (get_next_uint_value(&new_sector->lights.is_linked, buf, &pos, size))
		return (1);
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

	i = 0;
	if (get_next_uint_value(&new_sector->nb_of_msgs, buf, &pos, size))
		return (1);
	if (new_sector->nb_of_msgs)
		new_sector->story = (char **)malloc(sizeof(char *)
				* (new_sector->nb_of_msgs + 1));
	else
		new_sector->story = NULL;
	if (new_sector->nb_of_msgs && !new_sector->story)
		return (1);
	while (i < new_sector->nb_of_msgs)
	{
		if (get_next_string(&new_sector->story[i], buf, &pos, size))
			return (1);
		i++;
	}
	new_sector->cur_msg = 0;
	return (0);
}

int	parse_map_name(char **chosen_map, ssize_t size, unsigned char *buf,
	unsigned int **pos)
{
	size_t	len;

	**pos += get_next_breaker(buf + **pos) + 1;
	if (**pos > (unsigned int)size)
		return (1);
	len = get_next_breaker(buf + **pos);
	ft_strdel(chosen_map);
	*chosen_map = ft_strndup((const char *)buf + **pos, len - 1);
	if (!*chosen_map)
		error_output("Error when allocating memory for new mapname");
	return (0);
}
