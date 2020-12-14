/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:25:02 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:06:49 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *str, size_t n)
{
	size_t byte;

	byte = 0;
	while (str[byte] && (byte < n))
	{
		dst[byte] = str[byte];
		++byte;
	}
	if (str[byte] == '\0')
	{
		while (byte < n)
		{
			dst[byte] = '\0';
			++byte;
		}
	}
	return (dst);
}
