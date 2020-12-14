/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:20:34 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 20:58:46 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *str, void (*func)(char *))
{
	size_t i;

	if (str && func)
	{
		i = 0;
		while (str[i])
		{
			func(&str[i]);
			++i;
		}
	}
}
