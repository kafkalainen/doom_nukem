/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:37:32 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/26 11:09:36 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub_string;

	i = 0;
	sub_string = (char*)malloc(sizeof(*sub_string) * (len + 1));
	if (sub_string != NULL)
	{
		while (i < len)
		{
			sub_string[i] = s[start + i];
			i++;
		}
		sub_string[i] = '\0';
	}
	return (sub_string);
}
