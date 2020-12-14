/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:04:42 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/27 17:48:48 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t i;
	size_t length;

	if (str == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	while (i <= length)
	{
		if (str[i] == c)
			return (char *)(str + i);
		++i;
	}
	return (NULL);
}
