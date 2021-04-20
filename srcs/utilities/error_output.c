/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/20 18:42:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	error_output_sdl(char *msg, t_home *home)
{
	if (ft_strequ(msg, "Fatal: Failed to create a window."))
	{
		SDL_Quit();
	}
	if (ft_strequ(msg, "Fatal: Failed to get window surface"))
	{
		SDL_DestroyWindow(home->win.window);
		SDL_Quit();
	}
	if (ft_strequ(msg, "Fatal: SDL_mixer could not initialize!"))
	{
		SDL_DestroyWindow(home->win.window);
		SDL_Quit();
	}
	ft_putendl_fd(msg, 2);
	// clean_up(home, 5);
}

void	error_output(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	map_error_output(int i, t_home *home)
{
	if (i == 1)
		ft_putendl_fd("ERROR: Player not within the map.", 2);
	else if (i == 2)
		ft_putendl_fd("ERROR: Same points.", 2);
	else if (i == 3)
		ft_putendl_fd("ERROR: Portal not connected.", 2);
	else if (i == 4)
		ft_putendl_fd("ERROR: Sector not convex.", 2);
	else if (i == 5)
		ft_putendl_fd("ERROR: Sectors line segments are cutting.", 2);
	else if (i == 6)
		ft_putendl_fd("ERROR: Player out of bounds.", 2);
	free_sectors(home);
	exit(EXIT_FAILURE);
}

int		error_handling(int error_code, t_texture **tex)
{
	// free_full_colour_map(*tex);
	// ft_memdel((void**)tex);
	if (error_code == 1)
		ft_putendl_fd("ERROR: Malformed header data", 2);
	else if (error_code == 2)
		ft_putendl_fd("ERROR: Invalid height. Texture has to be 128 x 128", 2);
	else if (error_code == 3)
		ft_putendl_fd("ERROR: Invalid width. Texture has to be 128 x 128", 2);
	else if (error_code == 4)
		ft_putendl_fd("ERROR: Number of colours can't be zero.", 2);
	else if (error_code == 5)
		ft_putendl_fd("ERROR: Memory allocation of pixels failed.", 2);
	else if (error_code == 6)
		ft_putendl_fd("ERROR: Number of chars per pxl can't be zero.", 2);
	else if (error_code == 7)
		ft_putendl_fd("ERROR: Invalid colour id in pixel array.", 2);
	else if (error_code == 8)
		ft_putendl_fd("ERROR: Invalid number of pixels in array.", 2);
	else if (error_code == 9)
		ft_putendl_fd("ERROR: Invalid height in array.", 2);
	else if (error_code == 10)
		ft_putendl_fd("ERROR: Colour mapping failed.", 2);
	else
		ft_putendl_fd("ERROR: Undefined error.", 2);
	return (error_code);
}
