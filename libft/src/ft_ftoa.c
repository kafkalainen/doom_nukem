/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:40:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 19:07:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static void	ft_between_0_and_minus1(float nb, char **integer)
{
	char	*new_integer;

	if (nb < 0 && nb > -1)
	{
		new_integer = ft_strjoin("-", *integer);
		free(*integer);
		*integer = new_integer;
	}
}

char	*ft_ftoa(float nb, int precision)
{
	char	*integer;
	char	fraction[23];
	char	*total;
	int		i;

	i = 1;
	integer = ft_itoa((int)(nb));
	ft_between_0_and_minus1(nb, &integer);
	if (nb < 0)
		nb *= -1;
	nb = ft_roundf(nb, precision);
	nb = nb - (int)nb;
	fraction[0] = '.';
	while (nb && i < precision + 1)
	{
		nb *= 10;
		fraction[i] = (int)nb + '0';
		nb = nb - (int)nb;
		i++;
	}
	fraction[precision + 1] = '\0';
	total = ft_strjoin(integer, fraction);
	free(integer);
	return (total);
}
