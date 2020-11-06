/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/05 19:14:06 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void    ft_die(char *msg)
{
    printf("%s\n", msg);
    exit(0);
}

int  main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_die("Fatal: SDL Initalization failed.");
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (win == NULL)
        ft_die("Fatal: Failed to create a window.");
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
        ft_die("Fatal: Failed to create a renderer.");
    SDL_Texture *tex = new_surface_to_texture("hello_world.bmp", ren);
    while(1)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("Kossua!\n");
    return 0;
}
