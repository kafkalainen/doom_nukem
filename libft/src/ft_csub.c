/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:19:48 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 19:08:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_complex	ft_csub(t_complex x, t_complex y)
{
	t_complex	z;

	z.re = x.re - y.re;
	z.im = x.im - y.im;
	return (z);
}
