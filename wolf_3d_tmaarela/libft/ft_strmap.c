/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:36:00 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 22:14:23 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *str, char (*func)(char))
{
	char	*string;
	size_t	i;

	string = ft_strnew(ft_strlen(str));
	if (string != NULL)
	{
		i = 0;
		while (str[i])
		{
			string[i] = func(str[i]);
			++i;
		}
	}
	return (string);
}
