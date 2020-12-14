/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prime_nfactors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 23:16:15 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/20 18:18:48 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_prime_nfactors(unsigned int number)
{
	unsigned int count;
	unsigned int divisor;

	count = 0;
	divisor = 2;
	while (divisor <= number / 2 + 1)
	{
		while (number == 2 || number % divisor == 0)
		{
			++count;
			number /= divisor;
		}
		divisor += (divisor == 2 ? 1 : 2);
	}
	if (number > 2)
		++count;
	return (count);
}
