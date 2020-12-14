/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:59:05 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 20:12:34 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *src1, const void *src2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				byte;

	if (src1 && src2 && (src1 != src2) && (n > 0))
	{
		p1 = src1;
		p2 = src2;
		byte = 0;
		while (byte < n)
		{
			if (p1[byte] != p2[byte])
			{
				return (p1[byte] - p2[byte]);
			}
			++byte;
		}
	}
	return (0);
}
