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
		if (pos.x >= 0 && pos.x < SCREEN_WIDTH && pos.y >= 0 && pos.y < SCREEN_HEIGHT)
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

void	draw_rect_center(t_xy xy, t_xy wh, t_home home)
{
	double j;
	double i;

	i = -wh.x / 2;
	j = -wh.y / 2;
	while (j < wh.y / 2 && i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
	{
			ft_draw_line(vec2(xy.x + i, xy.y + j), vec2(xy.x + fabs(i), xy.y + j), 0x00A000, home.ren);
			j++;
	}
}

void	init_player(t_player *plr, t_xy pos)
{
	plr->pos.x = pos.x;
	plr->pos.y = pos.y;
	plr->pos.z = 0;
}

void	update_player(t_player *plr, t_home home, SDL_Event e)
{
	key_input(plr, e, home);
	draw_rect_center(vec2(plr->pos.x, plr->pos.y), vec2(16, 16), home);
}

int  main(int argc, char **argv)
{
    t_home		home;
	t_player	plr;
    SDL_Event	e;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_die("Fatal: SDL Initalization failed.", home);
    home.win.window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, 0);
    if (home.win.window == NULL)
       ft_die("Fatal: Failed to create a window.", home);
    home.ren = SDL_CreateRenderer(home.win.window, -1, SDL_RENDERER_ACCELERATED);
    if (home.ren == NULL)
      ft_die("Fatal: Failed to create a renderer.", home);
	init_player(&plr, vec2(128, 128));
    while(1)
    {
		SDL_SetRenderDrawColor(home.ren, 0, 0, 0, 255);
		SDL_RenderClear(home.ren);
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
			break;
		draw_grid(32, 32, home);
		update_player(&plr, home, e);
        SDL_RenderPresent(home.ren);
    }
    SDL_Quit();
    printf("Kossua!\n");
    return 0;
}
