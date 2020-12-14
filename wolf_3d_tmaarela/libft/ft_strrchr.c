/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:33:37 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/27 17:42:35 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	ssize_t	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			return (char *)(str + i);
		}
		--i;
	}
	return (NULL);
}
