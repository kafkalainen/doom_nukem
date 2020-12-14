/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:58:20 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 23:04:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *str, unsigned int start, size_t n)
{
	char	*string;
	size_t	i;

	string = ft_strnew(n);
	if (string != NULL)
	{
		i = 0;
		while (i < n)
		{
			string[i] = str[start + i];
			++i;
		}
	}
	else
	{
		ft_strdel(&string);
	}
	return (string);
}
