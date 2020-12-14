/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:52:22 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/26 05:11:20 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** If str == NULL, output placeholder.
** If n == MAX_SIZE_T, output whole string.
** Else output n characters.
*/

size_t	ft_putstrn(const char *str, size_t n)
{
	size_t length;

	if (str)
	{
		if ((ssize_t)n == (ssize_t)-1)
			length = ft_strlen(str);
		else
			length = n;
		write(1, str, length);
	}
	else
	{
		length = 6;
		write(1, "(null)", length);
	}
	return (length);
}
