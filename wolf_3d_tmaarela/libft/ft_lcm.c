/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:10:24 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 13:18:29 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lcm(unsigned int a, unsigned int b)
{
	unsigned int result;

	result = 0;
	if (a && b)
	{
		result = (a * b) / ft_hcf(a, b);
	}
	return (result);
}
