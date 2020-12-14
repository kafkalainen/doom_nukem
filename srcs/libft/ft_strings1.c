/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:43:13 by tmaarela          #+#    #+#             */
/*   Updated: 2020/12/14 13:43:13 by tmaarela         ###   ########.fr       */
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

size_t	ft_strclen(const char *str, int c)
{
	size_t length;

	length = 0;
	c = (unsigned char)c;
	if (str != NULL)
	{
		while (*str != c)
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

char	*ft_strdup(const char *str)
{
	return (ft_strcpy(ft_strnew(ft_strlen(str)), str));
}

int		ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)str1;
	p2 = (unsigned char *)str2;
	i = 0;
	while (p1[i] && (p1[i] == p2[i]))
		++i;
	return (p1[i] - p2[i]);
}

char	*ft_strsub(const char *str, unsigned int start, size_t n)
{
	char	*string;
	size_t	i;

	string = ft_strnew(n);
	if (string != NULL)
	{
		i = 0;
		while (i < n)
		{
			string[i] = str[start + i];
			++i;
		}
	}
	else
	{
		ft_strdel(&string);
	}
	return (string);
}

char	*ft_strcat(char *dst, const char *str)
{
	size_t length;

	length = ft_strlen(dst);
	ft_strcpy(dst + length, str);
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*string;

	string = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	string = ft_strcat(string, s1);
	string = ft_strcat(string, s2);
	return (string);
}
