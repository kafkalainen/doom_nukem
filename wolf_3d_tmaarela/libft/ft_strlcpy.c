/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 08:06:10 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/25 14:58:14 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *str, size_t n)
{
	char		*destination;
	const char	*string;
	size_t		bytes;

	destination = dst;
	string = str;
	bytes = n;
	while (*string && bytes > 1)
	{
		*(destination++) = *(string++);
		--bytes;
	}
	if (bytes && n)
		*destination = '\0';
	return (ft_strlen(str));
}
