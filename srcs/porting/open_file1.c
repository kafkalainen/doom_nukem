/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:28:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 17:39:49 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	get_map_header(unsigned int *pos, unsigned char **buf,
	t_home *home, ssize_t size)
{
	*buf = (unsigned char *)ft_strstr((const char *)*buf, "doom_nukem_sectors");
	if (!*buf)
		return (1);
	if (get_next_uint_value(&home->nbr_of_sectors, *buf, &pos, size))
		return (1);
	if (get_next_int_value(&home->end_sector, *buf, &pos, size))
		return (1);
	if (home->nbr_of_sectors <= 0 || home->end_sector < 0
		|| home->end_sector > (int)home->nbr_of_sectors)
		return (1);
	if (get_next_uint_value(&home->linked_map, *buf, &pos, size))
		return (1);
	if (home->linked_map)
	{
		if (parse_map_name(&home->map, size, *buf, &pos))
			return (1);
	}
	else
		ft_strdel(&home->map);
	return (0);
}

static int	get_plr(unsigned int *pos, unsigned char *buf,
			t_player *plr, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->pos.x = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->pos.z = ft_atoi((const char *)buf + *pos);
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	plr->start_sector = ft_atoi((const char *)buf + *pos);
	plr->cur_sector = plr->start_sector;
	plr->msg_sector = plr->start_sector;
	return (0);
}

int	free_sectors_and_exit(int error_code, t_home *home)
{
	if (error_code == 2)
	{
		free_sectors(home);
		ft_putendl_fd("ERROR: Still data in buffer after reading.", 2);
	}
	return (1);
}

int	parse_sector_data(unsigned char *buf, t_player *plr,
	t_home *home, ssize_t size)
{
	unsigned int	pos;
	unsigned int	i;

	i = 0;
	pos = 0;
	if (get_map_header(&pos, &buf, home, size) || get_plr(&pos, buf, plr, size))
		return (1);
	home->sectors = (t_sector **)malloc(sizeof(t_sector)
			* (home->nbr_of_sectors + 1));
	if (!home->sectors)
		return (1);
	while (i < home->nbr_of_sectors)
	{
		home->sectors[i] = get_sector_data(buf, &pos, size);
		if (home->sectors[i] == NULL)
			error_output("ERROR: Memory allocation for a sector failed.");
		i++;
	}
	pos += get_next_breaker(buf + pos);
	if (pos > (unsigned int)size
		|| !ft_strnequ((const char *)buf + pos, "#doom_nukem_entities", 20))
		return (free_sectors_and_exit(2, home));
	home->sectors[i] = NULL;
	return (0);
}

int	load_map_file(t_player *plr, t_home *home)
{
	int				fd;
	unsigned char	*buf;
	ssize_t			size;

	buf = (unsigned char *)malloc(sizeof(unsigned char) * (MAX_SIZE + 1));
	if (!buf)
		error_output("ERROR: Failed allocate memory for the map.");
	doom_open(&fd, (const char **)&home->map, READ_ONLY, 0644);
	if (fd < 0)
		error_output("ERROR: Failed to open map");
	else
	{
		doom_read(&size, &fd, (void **)&buf, MAX_SIZE);
		if (size <= 0 || size == MAX_SIZE || doom_close(&fd) == -1)
			read_error_output("ERROR: Failed to read map.", &buf);
		buf[size] = '\0';
		verify_hash(buf, size);
		parse_map_data(buf, plr, home, size);
		calc_map_properties(home, plr);
	}
	return (0);
}
