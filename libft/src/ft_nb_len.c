/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:03:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/03/24 17:35:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_nb_len(int value, int base)
{
	int		len;

	len = 0;
	if (value < 0 && base == 10)
		len++;
	if (value == 0)
		return (1);
	while (value)
	{
		len++;
		value /= base;
	}
	return (len);
}
