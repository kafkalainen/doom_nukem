/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_wrds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:15:06 by jnivala           #+#    #+#             */
/*   Updated: 2020/10/24 12:31:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_count_wrds(const char *s, int d)
{
	size_t	len;

	len = 0;
	if (s != 0)
	{
		while (*s != '\0')
		{
			while (*s == d || *s == '\n')
				s++;
			if (*s != d && *s != '\n' && *s != '\0')
				len++;
			while (*s != d && *s != '\n' && *s != '\0')
				s++;
		}
	}
	return (len);
}
