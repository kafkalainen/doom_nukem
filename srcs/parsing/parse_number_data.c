/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:23:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/29 11:06:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	parse_number_data(t_sector *new_sector, unsigned char *buf,
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
	new_sector->lights.state = TRUE;
	new_sector->lights.light_src = (t_xyz){0.8f, 9.0f, 6.0f, 1.0f};
	new_sector->lights.diffuse_power = 40.0f;
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
