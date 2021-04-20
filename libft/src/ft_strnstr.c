/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 11:16:09 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:43:06 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = 0;
	if (ft_strcmp(little, "") == 0)
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big != '\0' && len)
	{
		if (ft_strncmp((char *)big, little, little_len) == 0)
		{
			if (len >= little_len)
				return ((char *)big);
			else
				return (NULL);
		}
		big++;
		len--;
	}
	return (NULL);
}
