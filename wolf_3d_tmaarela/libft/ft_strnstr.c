/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:25:21 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/25 14:29:37 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t start;
	size_t i;

	if (!*needle)
		return ((char *)haystack);
	start = 0;
	while (haystack[start] && start < n)
	{
		i = 0;
		while (needle[i]
			&& haystack[start + i] == needle[i]
			&& (start + i) < n)
		{
			++i;
		}
		if (needle[i] == '\0')
			return ((char *)(haystack + start));
		++start;
	}
	return (NULL);
}
