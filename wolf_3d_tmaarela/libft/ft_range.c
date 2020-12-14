/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:28:10 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/20 18:20:18 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int		*array;
	size_t	i;

	array = NULL;
	if (min < max)
	{
		if ((array = (int *)malloc((max - min) * sizeof(int))))
		{
			i = 0;
			while (min < max)
			{
				array[i] = min;
				++i;
				++min;
			}
		}
	}
	return (array);
}
