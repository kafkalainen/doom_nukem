/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 09:24:41 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/26 10:03:16 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*str;

	i = 0;
	str = (char*)malloc(sizeof(*str) * (ft_strlen(s) + 1));
	if (str != NULL)
	{
		while (s[i] != '\0')
		{
			str[i] = s[i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
