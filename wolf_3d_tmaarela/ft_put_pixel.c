/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:05:14 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/13 23:38:21 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_put_pixel(int x, int y, int color, t_image *image)
{
	int index;
	int background;

	index = (y * image->line + x);
	if (index > 0 && index < WIN_WIDTH * WIN_HEIGHT)
	{
		background = image->data[index];
		image->data[index] = blend_argb(color, background);
		return (TRUE);
	}
	else
		return (FALSE);
}
