/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roundf_to_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:05:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/11 15:06:24 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_roundf_to_grid(float nb, int prec)
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
	if (nb > 0)
		nb += fraction;
	else
		nb -= fraction;
	return (nb);
}
