/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:08:52 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/23 15:17:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void	parse_sector_data(unsigned char *buf, unsigned int size, t_home *home)
{
	unsigned int	pos;
	unsigned int	i;

	i = 0;
	pos = 0;
	if (!(buf = ft_strstr((const char*)buf, "doom_sectors")))
		error_output("ERROR: No sector dataheader found");
	pos += get_next_breaker(buf + pos) + 1;
	home->nbr_of_sectors = ft_atoi(buf + pos);
	pos += ft_numlen(home->nbr_of_sectors);
	if (!(home->sectors = (t_sector**)malloc(sizeof(t_sector*) * (home->nbr_of_sectors + 1))))
		error_output("ERROR: Failed to allocate memory for game sectors\n");
	while (i < home->nbr_of_sectors)
	{
		home->sectors[i] = get_sector_data(buf, &pos);
		i++;
	}
	home->sectors[i] = NULL;
}

int		open_map_file(t_home *home, char *path)
{
	int				fd;
	unsigned char	*buf;
	unsigned int	size;

	if ((fd = OPEN_FILE(path, READ_ONLY)) < 0)
		error_output("Failed to open file\n");
	else
	{
		if (!(buf = (unsigned char *)malloc(sizeof(unsigned char) * MAX_SIZE))) // tone down the MAX_SIZE for this once we know the avg range of file sizes
			error_output("Memory allocation of source buffer failed\n");
		size = READ_FILE(fd, buf, MAX_SIZE);
		if (size <= 0)
			error_output("Failed to read file\n");
		else if (size >= MAX_SIZE)
			error_output("File is too large\n");
		if (CLOSE_FILE(fd) == -1)
			error_output("Could not close file\n");
		parse_sector_data(buf, size, home);
		free(buf);
	}
	return (1);
}
