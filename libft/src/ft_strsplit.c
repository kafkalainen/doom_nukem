/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 08:09:16 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/20 11:48:46 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_word_counter(char const *s, char c)
{
	size_t			i;
	size_t			word_count;

	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			word_count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word_count);
}

static size_t	ft_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static int		ft_divide_word(char const *s, size_t i, size_t len, char **arr)
{
	if (len > 0)
	{
		arr[i] = ft_strsub(s - len, 0, len);
		if (arr[i] != NULL)
			return (1);
		else
			return (0);
	}
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t			i;
	size_t			word_len;
	size_t			word_count;
	char			**arr;

	i = 0;
	if (s == NULL)
		return (NULL);
	word_count = ft_word_counter(s, c);
	if ((arr = (char**)malloc(sizeof(*arr) * (word_count + 1))))
	{
		while (i < word_count)
		{
			while (*s == c && *s != '\0')
				s++;
			word_len = ft_word_len(s, c);
			while (*s != c && *s != '\0')
				s++;
			if (ft_divide_word(s, i, word_len, arr) == 0)
				return (ft_strarrdel(&arr, word_count));
			i++;
		}
		arr[i] = NULL;
	}
	return (arr);
}
