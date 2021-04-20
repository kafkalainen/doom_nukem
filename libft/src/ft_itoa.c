/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:01:20 by jnivala           #+#    #+#             */
/*   Updated: 2020/06/29 15:36:23 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_nb_assign(int len, char *str, int n)
{
	int		temp;

	temp = 0;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		temp = n % 10;
		str[len - 1] = temp + '0';
		n = n / 10;
		len--;
	}
}

static int	ft_int_len(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
	{
		n = -214748364;
		i++;
	}
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		original_len;
	int		len;
	char	*str;

	len = ft_int_len(n);
	original_len = len;
	str = (char*)malloc(sizeof(*str) * (len + 1));
	if (str != NULL)
	{
		if (n == -2147483648)
		{
			str[len - 1] = 8 + '0';
			len--;
			n = -214748364;
		}
		if (n < 0)
		{
			str[0] = '-';
			n *= -1;
		}
		ft_nb_assign(len, str, n);
		str[original_len] = '\0';
	}
	return (str);
}
