/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:01:37 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 16:02:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_memstr(const char *haystack, const char *needle, size_t size)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (i < size)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp((char *)(haystack + i), needle, len) == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
