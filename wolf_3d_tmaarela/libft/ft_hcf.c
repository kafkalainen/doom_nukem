/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hcf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:13:12 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 13:17:28 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_hcf(unsigned int a, unsigned int b)
{
	unsigned int	result;
	unsigned int	high;
	unsigned int	low;
	unsigned int	remainder;

	result = 0;
	if (a && b)
	{
		high = (a > b ? a : b);
		low = (a < b ? a : b);
		remainder = 1;
		while (remainder)
		{
			remainder = high % low;
			if (remainder == 0)
			{
				result = low;
				break ;
			}
			high = low;
			low = remainder;
		}
	}
	return (result);
}
