/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:01:57 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:01:34 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *str)
{
	size_t byte;

	byte = 0;
	while (str[byte] != '\0')
	{
		dst[byte] = str[byte];
		++byte;
	}
	dst[byte] = '\0';
	return (dst);
}
