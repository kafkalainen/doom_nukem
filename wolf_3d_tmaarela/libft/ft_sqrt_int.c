/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:18:02 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 01:33:40 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_sqrt_int(unsigned int number)
{
	unsigned int root;
	unsigned int square;

	if (number == 0)
		return (0);
	root = 1;
	square = 1;
	while (square <= number)
	{
		++root;
		square = root * root;
	}
	return (root - 1);
}
