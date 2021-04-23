/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:23:28 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/23 12:50:00 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	parse_number_data(t_sector *new_sector, unsigned char *buf,
	unsigned int *pos)
{
	new_sector->idx_sector = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->idx_sector, 10) + 1;
	new_sector->nb_of_walls = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->nb_of_walls, 10) + 1;
	new_sector->ground = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->ground, 10) + 1;
	new_sector->ceiling = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->ceiling, 10) + 1;
	new_sector->tex_floor = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->tex_floor, 10) + 1;
	new_sector->tex_ceil = ft_atoi((const char *)buf + *pos);
	*pos += ft_nb_len(new_sector->tex_ceil, 10) + 1;
	return (0);
}

int	parse_coordinates(t_xy *coord, int *tex_id,
	unsigned int ***pos, unsigned char **buf)
{
	coord->x = ft_atoi((const char *)*buf + ***pos);
	***pos += ft_nb_len(coord->x, 10) + 1;
	coord->y = ft_atoi((const char *)*buf + ***pos);
	***pos += ft_nb_len(coord->y, 10) + 1;
	*tex_id = ft_atoi((const char *)*buf + ***pos);
	return (0);
}
