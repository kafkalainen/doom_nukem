/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:46:20 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/12 11:36:13 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	new_str = (char*)malloc(sizeof(*new_str) * (ft_strlen(s) + 1));
	if (new_str != NULL)
	{
		while (s[i] != '\0')
		{
			new_str[i] = f(s[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	else
		return (NULL);
}
