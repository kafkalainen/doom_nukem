/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:01:54 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/22 20:19:41 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	size_t	start;
	size_t	end;
	char	hold;

	if (str != NULL)
	{
		start = 0;
		end = ft_strlen(str) - 1;
		while (start < end)
		{
			hold = str[start];
			str[start] = str[end];
			str[end] = hold;
			++start;
			--end;
		}
	}
}
