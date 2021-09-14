/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:59:12 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/14 17:59:31 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

Uint32	ft_adler32(unsigned char *data, ssize_t size)
{
	Uint32	a;
	Uint32	b;
	ssize_t	i;

	i = 0;
	a = 0;
	b = 0;
	while (i < size)
	{
		a = (a + data[i]) % MOD_ADLER;
		b = (b + a) % MOD_ADLER;
		i++;
	}
	return ((b << 16 | a));
}

void	write_hash_to_file(unsigned char *path,
	unsigned char *buf, int hash, ssize_t size)
{
	int				fd;
	unsigned char	*tmp;

	tmp = NULL;
	doom_open(&fd, (const char **)&path,
		WRITE_ONLY | READ_ONLY | CREATE_FILE | TRUNCATE, 0644);
	if (fd < 0)
		error_output("failed to open file for hashing\n");
	tmp = (unsigned char *)ft_strjoin_freeable(ft_itoa(hash), "\n", 1, 0);
	if (doom_write(&fd, (const void **)&tmp,
			ft_strlen((const char *)tmp)) == -1)
		error_output("failed to write hash to file\n");
	if (doom_write(&fd, (const void **)&buf, size) == -1)
		error_output("failed to write map data\n");
	ft_strdel((char **)&tmp);
	ft_strdel((char **)&buf);
	doom_close(&fd);
}

void	create_hash(unsigned char *path)
{
	int				fd;
	unsigned char	*buf;
	ssize_t			size;
	Uint32			res;

	res = 0;
	buf = (unsigned char *)malloc(sizeof(unsigned char) * (MAX_SIZE + 1));
	if (!buf)
		error_output("ERROR: Failed allocate memory for the map.");
	doom_open(&fd, (const char **)&path, READ_ONLY, 0644);
	if (fd < 0)
		error_output("ERROR: Failed to open map");
	else
	{
		doom_read(&size, &fd, (void **)&buf, MAX_SIZE);
		if (size <= 0 || size == MAX_SIZE || doom_close(&fd) == -1)
			read_error_output("ERROR: Failed to read map.", &buf);
		buf[size] = '\0';
		res = ft_adler32(buf, size);
		write_hash_to_file(path, buf, res, size);
	}
}
