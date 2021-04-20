/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:40:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/26 10:52:09 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (s[i] != c && s[i])
	{
		words++;
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**array;

	k = 0;
	i = 0;
	if (!s || !(array = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		if (i)
		{
			if (!(array[k++] = ft_strncpy(ft_strnew(i), s, i)))
				return (NULL);
			s = &s[i];
		}
		else
			s++;
	}
	array[k] = NULL;
	return (array);
}
