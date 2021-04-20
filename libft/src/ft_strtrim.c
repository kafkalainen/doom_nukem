/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:01:24 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/30 09:27:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char		*ft_strtrim(char const *s)
{
	char				*trimmed_str;
	unsigned int		i;
	size_t				len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (len == 0)
	{
		trimmed_str = ft_strsub(s, 0, 0);
		return (trimmed_str);
	}
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i >= len)
	{
		trimmed_str = ft_strsub(s, len, 0);
		return (trimmed_str);
	}
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	trimmed_str = ft_strsub(s, i, len - i);
	return (trimmed_str);
}
