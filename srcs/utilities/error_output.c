/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:39:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/29 13:26:53 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	error_output_sdl(char *msg, t_home *home, t_frame *frame)
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
	clean_up(frame);
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
