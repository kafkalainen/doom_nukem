/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:43:09 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/16 12:51:04 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

void    error_output_sdl(char *msg, t_home *home)
{
    SDL_DestroyWindow(home->win.window);
    printf("%s\n", msg);
    exit(0);
}

void    error_output(char *msg)
{
    printf("%s\n", msg);
	exit(0);
}
