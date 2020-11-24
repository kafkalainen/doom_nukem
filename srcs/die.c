/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:43:09 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/20 15:43:09 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../doom_nukem.h"

void    ft_die(char *msg, t_home *home)
{
    SDL_DestroyRenderer(home->ren);
    SDL_DestroyWindow(home->win.window);
    printf("%s\n", msg);
    exit(0);
}
