/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roundf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:03:23 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:27:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_roundf(float nb, int prec)
{
	long double	fraction;

	if (prec < 0)
		return (nb);
	fraction = 0.5;
	while (prec)
	{
		fraction = fraction * 0.1;
		prec--;
	}
	nb += fraction;
	return (nb);
}
