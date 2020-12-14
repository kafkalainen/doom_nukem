/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:23:11 by ngontjar          #+#    #+#             */
/*   Updated: 2019/10/29 23:04:57 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strtrim(const char *str)
{
	char	*string;
	size_t	start;
	size_t	end;

	string = NULL;
	if (str != NULL)
	{
		start = 0;
		end = ft_strlen(str);
		while (start < end)
		{
			if (!ft_isspace(str[start]))
				break ;
			++start;
		}
		while (end > start && ft_isspace(str[--end]))
			;
		string = ft_strsub(str, start, end - start + 1);
	}
	return (string);
}
