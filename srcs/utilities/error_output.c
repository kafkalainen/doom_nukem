/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:43:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/20 16:20:52 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	error_output_sdl(char *msg, t_home *home)
{
	SDL_DestroyWindow(home->win.window);
	ft_putendl_fd(msg, 2);
	exit(0);
}

void	error_output(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(0);
}
