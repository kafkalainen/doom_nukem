/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:44:27 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/25 05:58:25 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long number)
{
	char				string[20 + 1];
	unsigned long long	num;
	unsigned int		length;

	if (number == 0)
		return (ft_strdup("0"));
	ft_memset(string, 0, 21);
	string[0] = '-';
	length = ft_numlen(number);
	num = (number < 0) ? -number : number;
	while (length--)
	{
		if (num)
			string[length] = '0' + (num % 10);
		num /= 10;
	}
	return (ft_strdup(string));
}
