/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 03:44:26 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/24 19:31:15 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_clamp(double in, double low, double high)
{
	if (in < low)
		return (low);
	else if (in > high)
		return (high);
	else
		return (in);
}
