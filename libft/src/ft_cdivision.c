/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdivision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:08:04 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:56:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_complex	ft_cdivision(t_complex x, t_complex y)
{
	t_complex	z;
	double		temp;
	double		div_x;
	double		div_y;

	z.re = 0.0;
	z.im = 0.0;
	if (y.re == 0 && y.im == 0)
		return (z);
	div_x = x.re * y.re + x.im * y.im;
	div_y = x.im * y.re - x.re * y.im;
	z.re = y.re * y.re + y.im * y.im;
	temp = div_x / z.re;
	z.im = div_y / z.re;
	z.re = temp;
	return (z);
}
