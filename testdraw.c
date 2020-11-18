/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testdraw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:45:46 by tmaarela          #+#    #+#             */
/*   Updated: 2020/11/06 17:45:46 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"

int		main(int argc, char **argv)
{
	SDL_Event ev;
	SDL_Event mm;
	SDL_Renderer *ren;
	SDL_Window *win;
	int x;
	int y;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(500, 500, 0, &win, &ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 128, 0, 255);
	while (1)
	{
		if (SDL_PollEvent(&ev) && ev.type == SDL_QUIT)
			break;
		if (SDL_PollEvent(&mm) && ev.type == SDL_MOUSEMOTION)
		{
			if (SDL_GetRelativeMouseState(NULL, NULL) & SDL_BUTTON_LEFT)
			{
				SDL_RenderDrawPoint(ren, mm.motion.x, mm.motion.y);
			}
		}
		SDL_RenderPresent(ren);
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
