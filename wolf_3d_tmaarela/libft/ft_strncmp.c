/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:27 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 22:14:44 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			bytes;

	p1 = (unsigned char *)str1;
	p2 = (unsigned char *)str2;
	bytes = 0;
	if (n > 0)
	{
		while (bytes < n)
		{
			if (!p1[bytes] || !p2[bytes] || (p1[bytes] != p2[bytes]))
				return (p1[bytes] - p2[bytes]);
			++bytes;
		}
	}
	return (0);
}
