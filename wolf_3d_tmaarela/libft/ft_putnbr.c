/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:25:55 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/22 19:25:32 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr)
{
	unsigned int number;

	if (nbr < 0)
	{
		ft_putchar('-');
		number = -nbr;
	}
	else
		number = nbr;
	if (number > 9)
	{
		ft_putnbr(number / 10);
		ft_putnbr(number % 10);
	}
	else
	{
		ft_putchar('0' + number);
	}
}
