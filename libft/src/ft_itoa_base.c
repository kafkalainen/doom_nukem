/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:21:36 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/17 08:48:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_intlen(int value, int base)
{
	int		len;

	len = 0;
	if (value < 0 && base == 10)
		len++;
	if (value == 0)
		return (1);
	while (value)
	{
		len++;
		value /= base;
	}
	return (len);
}

static void		ft_handle_special(int *pvalue, int *plen, int base, char **str)
{
	if (base == 10 && *pvalue == -2147483648)
	{
		*plen = 0;
		ft_strcpy(*str, "-2147483648");
	}
	if (*pvalue < 0 && *pvalue != -2147483648)
	{
		*pvalue *= -1;
		if (base == 10)
			*str[0] = '-';
	}
}

char			*ft_itoa_base(int value, int base)
{
	char	arr[17];
	char	*ret_arr;
	int		value_len;

	if (base < 2 || base > 16)
		return (0);
	ft_strcpy(arr, "0123456789ABCDEF");
	value_len = ft_intlen(value, base);
	if (!(ret_arr = (char*)malloc(sizeof(*ret_arr) * (value_len + 1))))
		return (NULL);
	ft_handle_special(&value, &value_len, base, &ret_arr);
	if (value_len > 0)
		ret_arr[value_len] = '\0';
	while (value)
	{
		value_len--;
		*(ret_arr + value_len) = arr[value % base];
		value /= base;
		if (value * base == -2147483648)
			value *= -1;
	}
	return (ret_arr);
}
