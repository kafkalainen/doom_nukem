/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:52:22 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/26 05:11:47 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** If str == NULL, output placeholder.
*/

size_t	ft_putstr(const char *str)
{
	size_t length;

	if (str)
	{
		length = ft_strlen(str);
		write(1, str, length);
	}
	else
	{
		length = 6;
		write(1, "(null)", length);
	}
	return (length);
}
