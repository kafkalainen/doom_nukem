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

void    ft_die(char *msg, t_home home)
{
    SDL_DestroyRenderer(home.ren);
    SDL_DestroyWindow(home.win.window);
    printf("%s\n", msg);
    exit(0);
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
	*(Uint32 *)target_pixel = pixel;
}

t_argb			int2argb(int color)
{
	return ((t_argb){
		(color >> 24) & 0xFF,
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		(color) & 0xFF
	});
}

int				ft_put_pixel(double x, double y, int color, SDL_Renderer *ren)
{
	t_argb c;
	
	c = int2argb(color);
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(ren, x, y);
}

int				ft_draw_line(t_xy start, t_xy end, int color, SDL_Renderer *ren)
{
	t_xy	length;
	t_xy	ratio;
	int		pixels;
	t_xy	pos;

	length = vec2(fabs(end.x - start.x), fabs(end.y - start.y));
	pixels = (length.x > length.y) ? (length.x) : (length.y);
	ratio.x = (start.y != end.y) ? (length.x / length.y) : 1;
	ratio.y = (start.x != end.x) ? (length.y / length.x) : 1;
	ratio.x = (ratio.x > ratio.y) ? 1 : (ratio.x);
	ratio.y = (ratio.y > ratio.x) ? 1 : (ratio.y);
	pos.x = start.x;
	pos.y = start.y;
	while (pixels-- > 0)
	{
		ft_put_pixel(pos.x, pos.y, color, ren);
		pos.x += ratio.x * ((start.x < end.x) ? 1 : -1);
		pos.y += ratio.y * ((start.y < end.y) ? 1 : -1);
	}
	return (TRUE);
}

void	draw_grid(int h, int v, t_home home)
{
	int i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ft_draw_line((t_xy){i, 0}, (t_xy){i, SCREEN_HEIGHT}, 0xFF8000, home.ren);
		i += h;
	}
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		ft_draw_line((t_xy){0, i}, (t_xy){SCREEN_WIDTH, i}, 0xFF8000, home.ren);
		i += v;
	}
}

int  main(int argc, char **argv)
{
    t_home home;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_die("Fatal: SDL Initalization failed.", home);
    home.win.window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (home.win.window == NULL)
       ft_die("Fatal: Failed to create a window.", home);
    home.ren = SDL_CreateRenderer(home.win.window, -1, SDL_RENDERER_ACCELERATED);
    if (home.ren == NULL)
      ft_die("Fatal: Failed to create a renderer.", home);
    while(1)
    {
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
			break;
        //SDL_RenderClear(home->ren);
		draw_grid(32, 32, home);
        SDL_RenderPresent(home.ren);
    }
    SDL_Quit();
    printf("Kossua!\n");
    return 0;
}
