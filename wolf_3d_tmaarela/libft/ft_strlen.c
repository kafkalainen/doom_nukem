/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:03:36 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 20:15:51 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t length;

	length = 0;
	if (str != NULL)
	{
		while (*str)
		{
			++length;
			++str;
		}
	}
	return (length);
}
