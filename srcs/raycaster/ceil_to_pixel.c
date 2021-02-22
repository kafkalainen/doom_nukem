/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_to_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 09:07:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/22 10:07:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ceil_to_pixel(float	nb)
{
	int		nb_as_integer;
	float	fraction;

	fraction = nb / 0.002454369f;
	nb_as_integer = (int)fraction;
	fraction = fraction - nb_as_integer;
	if (fraction)
		return ((nb_as_integer + 1.0f) * 0.002454369f);
	else
		return (nb);
}
