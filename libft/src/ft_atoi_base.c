/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 16:02:00 by jnivala           #+#    #+#             */
/*   Updated: 2020/10/23 18:18:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int		ft_static_base(const char *legal, int c, int base)
{
	int		i;

	i = 0;
	c = ft_toupper(c);
	while (i < base)
	{
		if (c == legal[i] || c == legal[i])
			return (i);
		i++;
	}
	return (-1);
}

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

int				ft_atoi_base(const char *nptr, int base)
{
	long int		integer;
	int				sign;
	char			legal[17];

	integer = 0;
	sign = 1;
	ft_strcpy(legal, "0123456789ABCDEF");
	while (ft_static_isspace(*nptr) > 0)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ft_static_base(legal, *nptr, base) != -1)
	{
		integer = integer * base;
		integer = integer + ft_static_base(legal, *nptr, base);
		nptr++;
	}
	return ((int)(sign * integer));
}
