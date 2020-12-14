/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:02:20 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/13 23:37:50 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_image			ft_new_image(int *mlx, int width, int height)
{
	t_image img;

	img.ptr = mlx_new_image(mlx, width, height);
	if (img.ptr == NULL)
	{
		return ((t_image){0});
	}
	img.data = (int *)mlx_get_data_addr(
		img.ptr, &img.bpp, &img.line, &img.endian);
	if (img.data == NULL)
	{
		mlx_destroy_image(mlx, img.ptr);
		return ((t_image){0});
	}
	img.line /= 4;
	img.width = width;
	img.height = height;
	return (img);
}

t_image			ft_new_xpm_image(int *mlx, char *filename)
{
	t_image img;

	img.ptr = mlx_xpm_file_to_image(mlx, filename, &img.width, &img.height);
	if (img.ptr == NULL)
	{
		return ((t_image){0});
	}
	img.data = (int *)mlx_get_data_addr(
		img.ptr, &img.bpp, &img.line, &img.endian);
	if (img.data == NULL)
	{
		mlx_destroy_image(mlx, img.ptr);
		return ((t_image){0});
	}
	img.line /= 4;
	return (img);
}
