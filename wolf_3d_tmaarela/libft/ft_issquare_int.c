/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issquare_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:35:19 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 01:46:04 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_issquare_int(unsigned int number)
{
	unsigned int root;

	root = ft_sqrt_int(number);
	return (number - (root * root) == 0);
}
