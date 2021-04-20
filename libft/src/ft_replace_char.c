/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:57:32 by jnivala           #+#    #+#             */
/*   Updated: 2020/10/26 17:43:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_replace_char(char *s, int c, int rep)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			*s = rep;
			i++;
		}
		s++;
	}
	return (i);
}
