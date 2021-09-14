/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:45:01 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/14 18:03:14 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	verify_hash(unsigned char *buf, ssize_t size)
{
	Uint32			orig_hash;
	Uint32			new_hash;
	ssize_t			pos;

	pos = 0;
	new_hash = 0;
	orig_hash = ft_atoi((const char *)buf);
	pos += get_next_breaker(buf + pos);
	if (pos > size)
		error_output("Reading past memory pointer\n");
	new_hash = ft_adler32(buf + pos, size - pos);
	if (orig_hash != new_hash)
		error_output("Hash verification failed\n");
	else
		ft_putstr("Verification successfull\n");
}
