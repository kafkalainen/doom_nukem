/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 13:47:24 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/01 09:58:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int		ft_static_isspace(int c)
{
	if (c == ' ')
		return (8192);
	else if (c == '\n')
		return (8192);
	else if (c == '\t')
		return (8192);
	else if (c == '\v')
		return (8192);
	else if (c == '\f')
		return (8192);
	else if (c == '\r')
		return (8192);
	else
		return (0);
}

int				ft_atoi(const char *nptr)
{
	size_t			i;
	long int		integer;
	int				sign;

	i = 0;
	integer = 0;
	sign = 1;
	while (ft_static_isspace(nptr[i]) > 0)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		integer = integer * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(sign * integer));
}
