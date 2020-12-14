/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:37:32 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:07:54 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *str, size_t n)
{
	size_t length;
	size_t bytes;

	length = ft_strlen(dst);
	bytes = 0;
	while (str[bytes] && (bytes < n))
	{
		dst[length + bytes] = str[bytes];
		++bytes;
	}
	dst[length + bytes] = '\0';
	return (dst);
}
