/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:44:53 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/24 14:05:22 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void			init_crc_table(t_crc *crc)
{
	int				i;
	int				j;
	unsigned int	k;

	i = -1;
	while (++i < 256)
	{
		k = (unsigned int)i;
		j = -1;
		while (++j < 8)
		{
			if (k & 1)
				k = 0xedb88320L ^ (k >> 1);
			else
				k = k >> 1;
		}
		crc->crc_table[i] = k;
	}
	crc->flag = 1;
}

unsigned int	update_crc(unsigned int crcbuf, unsigned char *buf,
	int size, t_crc *crc)
{
	unsigned int	i;
	int				x;

	i = crcbuf;
	if (!crc->flag)
		init_crc_table(crc);
	x = -1;
	while (++x < size)
	{
		i = crc->crc_table[(i ^ buf[x]) & 0xff] ^ (i >> 8);
	}
	return (i);
}

unsigned int	calculate_crc(unsigned char *buf, int size, t_crc *crc)
{
	return (update_crc(0xffffffffL, buf, size, crc) ^ 0xffffffffL);
}

void			verify_crc(unsigned char *crc_buf, unsigned char *buf,
	int size, t_crc *crc)
{
	int	current_crc;
	int	calc_crc;

	current_crc = get_big_endian(crc_buf);
	calc_crc = calculate_crc(buf, size, crc);
	if (current_crc != calc_crc)
		error_output("CRC not valid\n");
}
