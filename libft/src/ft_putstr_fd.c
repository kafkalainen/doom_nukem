/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 09:42:13 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/06 17:28:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_putstr_fd(char const *s, int fd)
{
	ssize_t	ret;

	ret = write(fd, s, ft_strlen(s));
	(void)ret;
	return ;
}
