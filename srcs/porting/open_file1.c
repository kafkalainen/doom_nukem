/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:28:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/01 14:46:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	get_map_header_data(unsigned int *pos, unsigned char *buf,
	unsigned int *nbr_of_sectors, ssize_t size)
{
	*pos += get_next_breaker(buf + *pos) + 1;
	if (*pos > (unsigned int)size)
		return (1);
	*nbr_of_sectors = ft_atoi((const char *)buf + *pos);
	if (*nbr_of_sectors <= 0)
		return (1);
	return (0);
}

static int	get_player_position(unsigned int *pos, unsigned char *buf,
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
	plr->cur_sector = ft_atoi((const char *)buf + *pos);
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
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_sectors");
	if (!buf)
		return (1);
	if (get_map_header_data(&pos, buf, &home->nbr_of_sectors, size)
		|| get_player_position(&pos, buf, plr, size))
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
	pos += get_next_breaker(buf + pos) + 1;
	if (pos > (unsigned int)size || *(buf + pos) != '\n')
		return (free_sectors_and_exit(2, home));
	home->sectors[i] = NULL;
	return (0);
}

/*
**	Add safeguards for mallocing.
*/

int	load_map_file(t_player *plr, t_home *home, char *path)
{
	int				fd;
	unsigned char	*buf;
	ssize_t			size;
	int				ret;

	buf = (unsigned char *)malloc(sizeof(unsigned char) * (BUF_SIZE + 1));
	if (!buf)
		error_output("ERROR: Failed allocate memory for the map.");
	doom_open(&fd, (const char **)&path, TEXT_ONLY, 0644);
	if (fd < 0)
		error_output("ERROR: Failed to open map");
	else
	{
		doom_read(&size, &fd, (void **)&buf, BUF_SIZE);
		if (size <= 0 || size == BUF_SIZE || doom_close(&fd) == -1)
			read_error_output("ERROR: Failed to read map.", &buf);
		buf[size] = '\0';
		ret = parse_sector_data(buf, plr, home, size);
		free(buf);
		if (ret)
			error_output("ERROR: Failed to read map.");
		validate_sectors_data(home, plr);
		calc_map_properties(home, plr);
		// ft_putstr("OK\n");
		// exit(0);
	}
	return (0);
}
