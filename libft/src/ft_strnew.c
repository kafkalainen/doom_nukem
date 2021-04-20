/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:24:51 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/30 23:17:47 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char *new_str;

	new_str = (char*)malloc(sizeof(*new_str) * size + 1);
	if (new_str != NULL)
	{
		ft_bzero(new_str, size + 1);
		return (new_str);
	}
	return (NULL);
}
