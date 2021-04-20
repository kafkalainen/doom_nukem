/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:52:27 by jnivala           #+#    #+#             */
/*   Updated: 2020/12/15 10:19:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	ft_cadd(t_complex x, t_complex y)
{
	t_complex z;

	z.re = x.re + y.re;
	z.im = x.im + y.im;
	return (z);
}
