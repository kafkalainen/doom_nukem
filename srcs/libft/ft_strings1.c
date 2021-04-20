/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:43:13 by tmaarela          #+#    #+#             */
/*   Updated: 2021/03/03 14:31:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

size_t	ft_strlen(const char *str)
{
	size_t length;

	length = 0;
	if (str != NULL)
	{
		while (*str)
		{
			++length;
			++str;
		}
	}
	return (length);
}

char	*ft_strnew(size_t size)
{
	char	*pointer;

	pointer = (char *)malloc(size + 1);
	if (pointer != NULL)
	{
		ft_memset(pointer, '\0', size + 1);
	}
	return (pointer);
}

void	ft_strdel(char **p)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}

char	*ft_strchr(const char *str, int c)
{
	size_t i;
	size_t length;

	if (str == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	while (i <= length)
	{
		if (str[i] == c)
			return (char *)(str + i);
		++i;
	}
	return (NULL);
}

char	*ft_strcpy(char *dst, const char *str)
{
	size_t byte;

	byte = 0;
	while (str[byte] != '\0')
	{
		dst[byte] = str[byte];
		++byte;
	}
	dst[byte] = '\0';
	return (dst);
}
