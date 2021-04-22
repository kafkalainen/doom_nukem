/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:28:46 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/22 15:44:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	free_sectors_and_exit(int error_code, t_home *home, size_t n)
{
	if (error_code == 1)
	{
		free_sectors_n(home, n);
		ft_putendl_fd("ERROR: Memory allocation for a sector failed.", 2);
	}
	else if (error_code == 2)
	{
		free_sectors(home);
		ft_putendl_fd("ERROR: Still data in buffer after reading.", 2);
	}
	return (1);
}

int	parse_sector_data(unsigned char *buf, t_home *home)
{
	unsigned int	pos;
	unsigned int	i;

	i = 0;
	pos = 0;
	buf = (unsigned char *)ft_strstr((const char *)buf, "doom_nukem_sectors");
	if (!buf)
		return (1);
	pos += get_next_breaker(buf + pos) + 1;
	home->nbr_of_sectors = ft_atoi((const char *)buf + pos);
	pos += ft_nb_len(home->nbr_of_sectors, 10);
	home->sectors = (t_sector **)malloc(sizeof(t_sector)
			* (home->nbr_of_sectors + 1));
	if (!home->sectors)
		return (1);
	while (i < home->nbr_of_sectors)
	{
		home->sectors[i] = get_sector_data(buf, &pos);
		if (home->sectors[i] == NULL)
			return (free_sectors_and_exit(1, home, i + 1));
		i++;
	}
	if (*(buf + pos) != '\0')
		return (free_sectors_and_exit(2, home, home->nbr_of_sectors));
	home->sectors[i] = NULL;
	return (0);
}

/*
**	Add safeguards for mallocing.
*/

int	load_map_file(t_home *home, char *path)
{
	int				fd;
	unsigned char	*buf;
	ssize_t			size;
	int				ret;

	buf = (unsigned char *)malloc(sizeof(unsigned char) * (BUF_SIZE + 1));
	if (!buf)
		error_output("ERROR: Failed allocate memory for the map.");
	doom_open(&fd, (const char **)&path, READ_ONLY);
	if (fd < 0)
		error_output("ERROR: Failed to open map");
	else
	{
		doom_read(&size, &fd, (void **)&buf, BUF_SIZE);
		if (size <= 0)
			error_output("ERROR: Failed to read map.");
		if (doom_close(&fd) == -1)
			error_output("ERROR: Could not close the file.");
		buf[size] = '\0';
		ret = parse_sector_data(buf, home);
		free(buf);
		if (ret)
			return (1);
		validate_sectors_data(home);
		calc_normal_vectors(home);
	}
	return (0);
}
