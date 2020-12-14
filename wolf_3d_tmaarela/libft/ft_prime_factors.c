/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prime_factors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 23:16:43 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/27 23:30:50 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	*ft_prime_factors(unsigned int number)
{
	unsigned int	*array;
	unsigned int	divisor;
	unsigned int	i;

	if ((array = (unsigned int *)malloc(
		sizeof(int) * (ft_prime_nfactors(number) + 1))))
	{
		divisor = 2;
		i = 0;
		while (divisor <= number / 2 + 1)
		{
			while (number == 2 || number % divisor == 0)
			{
				array[i++] = divisor;
				number /= divisor;
			}
			divisor += (divisor == 2 ? 1 : 2);
		}
		if (number > 2)
			array[i++] = number;
		array[i] = 0;
	}
	return (array);
}
