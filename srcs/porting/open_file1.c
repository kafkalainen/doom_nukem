/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:08:52 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/23 12:59:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

t_point				*new_point(t_xy x0, int idx)
{
	t_point		*new;

	new = (t_point*)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0 = x0;
		new->idx = idx;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

t_point				*add_point(t_point **point, t_point *new)
{
	t_point *temp;

	if (new == NULL)
		return ;
	if (*point == NULL)
	{
		*point = new;
	}
	else
	{
		temp = *point;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

t_point				*add_points(t_sector *sector, unsigned char *buf, unsigned int  **pos)
{
	size_t		walls;
	t_point		*temp;
	t_xy		coord;
	int			tex_id;

	walls = sector->nb_of_walls;
	sector->points = NULL;
	while (walls--)
	{
		coord.x = ft_atoi(buf + **pos);
		**pos += ft_numlen(coord.x) + 1;
		coord.y = ft_atoi(buf + **pos);
		**pos += ft_numlen(coord.y) + 1;
		tex_id = ft_atoi(buf + **pos);
		**pos += ft_numlen(tex_id) + 1;
		add_point(&sector->points, new_point(coord, tex_id));
	}
	temp = sector->points;
	while (temp->next)
		temp = temp->next;
	temp->next = sector->points;
}

t_sector			*get_sector_data(unsigned char *buf, unsigned int *pos)
{
	t_sector		*new_sector;

	if (!buf)
		return (NULL);
	if (!(new_sector = (t_sector*)malloc(sizeof(t_sector))))
		error_output("ERROR: Memory allocation for a sector failed.");
	*pos += get_next_breaker(buf + *pos) + 1;
	if (!ft_strstr((const char*)(buf + *pos), "sector"))
		error_output("ERROR: Uncorrect number of sectors given");
	*pos += 6;
	new_sector->idx_sector = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->idx_sector) + 1;
	new_sector->nb_of_walls = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->nb_of_walls) + 1;
	new_sector->ground = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->ground) + 1;
	new_sector->ceiling = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->ceiling) + 1;
	new_sector->tex_floor = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->tex_floor) + 1;
	new_sector->tex_ceil = ft_atoi(buf + *pos);
	*pos += ft_numlen(new_sector->tex_ceil) + 1;
	add_points(new_sector, buf, &pos);
	return (new_sector);
}

void				parse_sector_data(unsigned char *buf,
	unsigned int size, t_home *home)
{
	unsigned int	pos;
	unsigned int	i;

	pos = 0;
	if (!(buf = ft_strstr((const char*)buf, "doom_sectors")))
		error_output("ERROR: No sector dataheader found");
	pos += get_next_breaker(buf + pos) + 1;
	home->nbr_of_sectors = ft_atoi(buf + pos);
	pos += ft_numlen(home->nbr_of_sectors);
	if (!(home->sectors = (t_sector**)malloc(sizeof(t_sector*) * (home->nbr_of_sectors + 1))))
		error_output("ERROR: Failed to allocate memory for game sectors\n");
	i = 0;
	while (i < home->nbr_of_sectors)
	{
		home->sectors[i] = get_sector_data(buf, &pos);
		i++;
	}
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
