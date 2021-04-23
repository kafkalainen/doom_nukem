/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/23 14:24:36 by jnivala          ###   ########.fr       */
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
	clean_up(home);
}

void	error_output(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	read_error_output(char *msg, unsigned char **buf)
{
	ft_strdel((char **)buf);
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
