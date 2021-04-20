/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:45:59 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/09 12:42:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(needle);
	i = 0;
	if (j == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		if (ft_strncmp((haystack + i), needle, j) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
