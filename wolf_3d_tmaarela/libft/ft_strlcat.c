/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:03:35 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/25 16:43:59 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *str, size_t n)
{
	char	*destination;
	size_t	bytes;
	size_t	length;

	destination = dst;
	bytes = n;
	while (*destination && bytes)
	{
		++destination;
		--bytes;
	}
	length = destination - dst;
	bytes = n - length;
	return (length + ft_strlcpy(destination, str, bytes));
}
