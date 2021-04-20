/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpow3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:59:47 by jnivala           #+#    #+#             */
/*   Updated: 2020/12/23 10:09:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex		ft_cpow3(t_complex z)
{
	t_complex	result;

	result = ft_cmultiply(z, z);
	result = ft_cmultiply(result, z);
	return (result);
}
