/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:24:50 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 21:40:38 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*func)(unsigned int, char *))
{
	unsigned int i;

	if (str && func)
	{
		i = 0;
		while (str[i])
		{
			func(i, &str[i]);
			++i;
		}
	}
}
