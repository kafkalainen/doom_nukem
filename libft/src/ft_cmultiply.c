/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmultiply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:46:06 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 19:05:48 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_complex	ft_cmultiply(t_complex x, t_complex y)
{
	t_complex	z;

	z.re = x.re * y.re - x.im * y.im;
	z.im = x.re * y.im + x.im * y.re;
	return (z);
}
