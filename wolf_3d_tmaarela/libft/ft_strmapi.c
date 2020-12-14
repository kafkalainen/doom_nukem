/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:36:00 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 21:39:34 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*func)(unsigned int, char))
{
	char			*string;
	unsigned int	i;

	string = ft_strnew(ft_strlen(str));
	if (string != NULL)
	{
		i = 0;
		while (str[i])
		{
			string[i] = func(i, str[i]);
			++i;
		}
	}
	return (string);
}
