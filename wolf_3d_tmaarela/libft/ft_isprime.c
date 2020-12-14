/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:20:09 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 02:22:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_isprime(unsigned int number)
{
	unsigned int divisor;
	unsigned int max;

	divisor = 2;
	max = ft_sqrt_int(number);
	while (divisor <= max)
	{
		if (number % divisor == 0)
			return (0);
		++divisor;
	}
	return (number > 1);
}
