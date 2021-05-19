/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/18 15:52:16 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"

void			editor_put_pixel(Uint32 *buffer, int x, int y, int color)
{
	Uint32		*pixel;

	if (x > 1920 - 1 || y > 1080 - 1 || x < 0 || y < 0)
		return ;
	// buffer[(SCREEN_WIDTH * y) + x] = color;
	pixel = buffer + (1920 * y) + x;
	*pixel = color;
}

void	editor_draw_line(t_xy p0, t_xy p1, int colour, Uint32 *buffer)
{
	t_xy		delta;
	t_xy		pixel;
	long int	pixels;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = p0.x;
	pixel.y = p0.y;
	while (pixels)
	{
		editor_put_pixel(buffer, (int)pixel.x, (int)pixel.y, colour);
		pixel.x += delta.x;
		pixel.y += delta.y;
		--pixels;
	}
}

void	draw_box(t_xy start, t_xy end, Uint32 *buffer, int color)
{
	float y;
	float x;

	x = start.x;
	y = start.y;
	while (y < end.y)
	{
		editor_draw_line(vec2(x, y), vec2(end.x, y), color, buffer);
		y++;
	}
}

void		draw_buttons(t_button **blist, Uint32 *buffer)
{
	int	i;

	i = 0;
	//check_button_clicked(home, blist);
	while (i < NBR_BUTTONS)
	{
		draw_box(blist[i]->ltop, blist[i]->wh, buffer, 0xAAAAAA);
		i++;
		//draw_text(home, blist->text, vec2(blist->ltop.x + 8,
		//blist->ltop.y + 4), (t_color){0, 0, 0, 255});
		//blist = blist->next;
	}
	// hard coded UI text
	//draw_text(home, ft_itoa(home->sector_walls), vec2(148, 184), (t_color){0, 0, 0, 255});
	//draw_text(home, "Grid size: ", vec2(16, 112), (t_color){0, 0, 0, 255});
	//draw_text(home, ft_itoa(home->grid_size), vec2(60, 138), (t_color){0, 0, 0, 255});
}

void			draw_grid_editor(t_editor *editor, t_xy start, t_xy wh, int cell_size)
{
	int		i;

	i = 0;
	while (i < wh.x)
	{
		editor_draw_line(vec2(i + start.x, start.y), vec2(i + start.x, start.y + wh.y),
		0x606060, editor->buffer);
		i += cell_size;
	}
	i = 0;
	while (i < wh.y)
	{
		editor_draw_line(vec2(start.x, start.y + i), vec2(start.x + wh.x, start.y + i),
		0x606060, editor->buffer);
		i += cell_size;
	}
}

void	draw_ui(t_editor *editor)
{
	draw_box(vec2(0, 0), vec2(200, 1080), editor->buffer, 0x282040);
	if (editor->toggle_grid == 1)
		draw_grid_editor(editor, vec2(200, 0), vec2(1920, 1080), editor->grid_size);
	//draw_sectors(home);
}

void	init_mouse_data(t_mouse_data *mouse_data)
{
	mouse_data->i_mbleft = 0;
	mouse_data->i_mbright = 0;
	mouse_data->selected = -1;
	mouse_data->x = 0;
	mouse_data->y = 0;
	mouse_data->x_rel = 0;
	mouse_data->y_rel = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void	launch_editor(t_home *home, SDL_Event *e)
{
	t_button	**blist;
	t_editor	editor;
	int			i;
	int			w;
	int			h;

	w = 0;
	h = 0;
	SDL_SetWindowSize(home->win.window, 1920, 1080);
	SDL_GetWindowSize(home->win.window, &w, &h);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
	blist = (t_button **)malloc(sizeof(t_button*) * NBR_BUTTONS);
	init_textures(home);
	init_mouse_data(&editor.mouse_data);
	if (!(editor.buffer = (Uint32*)malloc(sizeof(Uint32) *
		(Uint32)w * (Uint32)h)))
		error_output("Memory allocation failed!\n");
	editor.grid_size = 32;
	editor.toggle_grid = 1;
	editor.button_list = create_button_list(blist);
	while (home->game_state == EDITOR)
	{
		editor_events(e, home, &editor);
		draw_ui(&editor);
		draw_buttons(blist, editor.buffer);
		render_buffer(editor.buffer, home->win.ScreenSurface);
		SDL_UpdateWindowSurface(home->win.window);
	}
	free(editor.buffer);
	i = -1;
	while (++i < NBR_BUTTONS)
	{
		free(blist[i]->text);
		free(blist[i]);
	}
	free(blist);
	free_all_textures(home->editor_tex, &home->nbr_of_textures);
	SDL_SetWindowFullscreen(home->win.window, 0);
	SDL_SetWindowSize(home->win.window, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowPosition(home->win.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
}