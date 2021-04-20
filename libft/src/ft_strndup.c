/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:58:13 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/09 09:59:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t		i;
	char		*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)malloc(sizeof(*str) * (n + 1));
	if (str != NULL)
	{
		while (n)
		{
			str[i] = s[i];
			i++;
			n--;
		}
	}
	str[i] = '\0';
	return (str);
}
