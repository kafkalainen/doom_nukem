/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:31:03 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/20 15:31:03 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int		ft_numlen(long number)
{
	char length;

	if (number == 0)
		return (1);
	length = (number < 0);
	number = (number < 0) ? -number : number;
	while (number)
	{
		++length;
		number /= 10;
	}
	return (length);
}

char	*ft_itoa(long long number)
{
	char				string[20 + 1];
	unsigned long long	num;
	unsigned int		length;

	if (number == 0)
		return (strdup("0"));
	memset(string, 0, 21);
	string[0] = '-';
	length = ft_numlen(number);
	num = (number < 0) ? -number : number;
	while (length--)
	{
		if (num)
			string[length] = '0' + (num % 10);
		num /= 10;
	}
	return (strdup(string));
}
