/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:53:16 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/22 13:09:20 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	doom_open(int *fd, const char **path, int mode)
{
	if (OS_WINDOWS)
		*fd = _open(*path, mode);
	else
		*fd = open(*path, mode);
}

int	doom_close(int *fd)
{
	int		ret;

	if (OS_WINDOWS)
		ret = _close(*fd);
	else
		ret = close(*fd);
	return (ret);
}

void	doom_read(ssize_t *read_bytes, int *fd, void **buf, size_t nb_of_bytes)
{
	if (OS_WINDOWS)
		*read_bytes = _read(*fd, *buf, nb_of_bytes);
	else
		*read_bytes = read(*fd, *buf, nb_of_bytes);
}
