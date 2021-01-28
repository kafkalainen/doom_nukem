/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:34:26 by tomtom            #+#    #+#             */
/*   Updated: 2020/01/11 16:25:03 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

unsigned long long	ft_numlength_base(long long num, int base)
{
	int ret;

	ret = 1;
	if (num < 0)
		ret++;
	while (num / base != 0)
	{
		num /= base;
		ret++;
	}
	return (ret);
}

int							count_zeros(long double num, int *prec)
{
	int		ret;
	int		i;

	i = *prec;
	ret = 0;
	while (i-- > 0)
	{
		num *= 10;
		if (num > -1 && num < 1)
		{
			ret++;
			*prec -= 1;
		}
	}
	return (ret);
}

static long double			ft_change_prec(long double n, int prec)
{
	int		i;

	i = 0;
	while (i < prec)
	{
		n = n * 10;
		i++;
	}
	return (n);
}

char						*add_zeros(int amount)
{
	char	*ret;

	if (!(ret = (char *)malloc(amount + 1)))
		return (NULL);
	ret[amount] = '\0';
	while (amount - 1 >= 0)
	{
		ret[amount - 1] = '0';
		amount--;
	}
	return (ret);
}

long double					pwten(long double num, int power)
{
	while (power-- > 0)
		num *= 10;
	return (num);
}

long double			ft_round(long double num, int prec)
{
	long double rv;

	rv = (long double)1 / 2;
	while (prec-- > 0)
		rv /= 10;
	num += rv;
	return (num);
}

char						*ft_ftoa(long double num, int prec, int dot)
{
	char			*ret;
	long double		n;
	int				i;
	int				neg;
	int				len;

	neg = (num < 0) ? 1 : 0;
	n = (num < 0) ? num * -1 : num;
	prec = (prec == -1 || prec > 19) ? 6 : prec;
	dot = (prec > 0 || dot == 1) ? 1 : 0;
	len = ft_numlength_base((long long)n, 10);
	if (!(ret = (char *)malloc(len + neg + prec + 1)))
		return (NULL);
	n = ft_round(n, prec);
	ret = ft_itoa((long long)n);
	n -= (long long)n;
	i = count_zeros(n, &prec);
	n = pwten(n, i);
	ret = (dot == 1) ? ft_strjoin(ret, ".") : ft_strjoin(ret, "");
	ret = ft_strjoin(ret, add_zeros(i));
	n = ft_change_prec(n, prec);
	((long long)n != 0) ? ret = ft_strjoin(ret, ft_itoa(n)) : 0;
	(neg == 1) ? ret = ft_strjoin("-", ret) : NULL;
	return (ret);
}