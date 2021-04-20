/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <joonas.hj.nivala@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:22:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/03 14:28:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

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

char	*ft_strdup(const char *str)
{
	return (ft_strcpy(ft_strnew(ft_strlen(str)), str));
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
