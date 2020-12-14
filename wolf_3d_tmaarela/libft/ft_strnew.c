/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:21:22 by ngontjar          #+#    #+#             */
/*   Updated: 2019/11/28 15:32:17 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*pointer;

	pointer = (char *)malloc(size + 1);
	if (pointer != NULL)
	{
		ft_memset(pointer, '\0', size + 1);
	}
	return (pointer);
}
