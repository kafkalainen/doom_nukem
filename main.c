#include <SDL2/SDL.h>
#include <libc.h>
#include <stdio.h>

void    ft_die(char *msg)
{
    printf("%s\n", msg);
    exit(0);
}

int     main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_die("Shiiiiit\n");
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (win == NULL)
        ft_die("Shiiiiit\n");
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL)
        ft_die("Shiiiiit\n");
    SDL_Surface *bmp = SDL_LoadBMP("hello_world.bmp");
    if (bmp == NULL)
        ft_die("Shiiiiit asd\n");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL)
        ft_die("Shiiiiit\n");

    while(1)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        //First clear the renderer
        SDL_RenderClear(ren);
        //Draw the texture
        SDL_RenderCopy(ren, tex, NULL, NULL);
        //Update the screen
        SDL_RenderPresent(ren);
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("SDL init success!\n");
    return 0;
}