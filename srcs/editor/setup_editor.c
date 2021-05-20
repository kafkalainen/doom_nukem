/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:47:35 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/20 11:21:07 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/doom_nukem.h"


void	put_editor_pixel(Uint32 *buffer, t_pxl_coords pxl_coords, t_screen_resolution dim, Uint32 color)
{
	if (pxl_coords.x > dim.width - 1 || pxl_coords.y > dim.height - 1 ||
		pxl_coords.x < 0 || pxl_coords.y < 0)
		return ;
	buffer[(dim.width * pxl_coords.y) + pxl_coords.x] = color;
}

void	editor_draw_line(t_box box, t_screen_resolution dim, int colour, Uint32 *buffer)
{
	t_xy			delta;
	t_pxl_coords	pixel;
	long int		pixels;

	delta.x = box.end.x - box.start.x;
	delta.y = box.end.y - box.start.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = (int)box.start.x;
	pixel.y = (int)box.start.y;
	while (pixels)
	{
		put_editor_pixel(buffer, pixel, dim, colour);
		pixel.x += (int)delta.x;
		pixel.y += (int)delta.y;
		--pixels;
	}
}

void	draw_box(t_box box, t_screen_resolution dim, Uint32 *buffer, int color)
{
	float end;
	float start;

	end = box.end.y;
	start = box.start.y;
	box.end.y = box.start.y;
	while (start < end)
	{
		box.start.y = start;
		box.end.y = box.start.y;
		editor_draw_line(box, dim, color, buffer);
		start++;
	}
}

void		draw_buttons(t_button **blist, Uint32 *buffer, t_screen_resolution dim)
{
	int		i;
	t_box	box;

	i = 0;
	//check_button_clicked(home, blist);
	while (i < NBR_BUTTONS)
	{
		box.start = blist[i]->ltop;
		box.end = blist[i]->wh;
		draw_box(box, dim, buffer, 0xAAAAAA);
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

void			draw_grid_editor(t_editor *editor, t_box box, int cell_size)
{
	t_box	copy;
	int		i;
	float	x;
	float	end;

	copy = box;
	i = 0;
	x = copy.start.x;
	end = copy.end.x;
	while (i < end)
	{
		copy.start.x = x + i;
		copy.end.x = copy.start.x;
		editor_draw_line(copy, editor->dim, 0x606060, editor->buffer);
		i += cell_size;
	}
	i = 0;
	copy = box;
	end = copy.end.y;
	x = copy.start.y;
	while (i < end)
	{
		copy.start.y = x + i;
		copy.end.y = copy.start.y;
		editor_draw_line(copy, editor->dim, 0x606060, editor->buffer);
		i += cell_size;
	}
}

void	draw_ui(t_editor *editor)
{
	t_box	box;

	box.start = vec2(0, 0);
	box.end = vec2(200, editor->dim.height);
	draw_box(box, editor->dim, editor->buffer, 0x282040);
	if (editor->toggle_grid == 1)
	{
		box.start = vec2(200, 0);
		box.end.x = (float)editor->dim.width;
		box.end.y = (float)editor->dim.height;
		draw_grid_editor(editor, box, editor->grid_size);
	}
	// draw_sectors(home);
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

	editor.dim.width = 0;
	editor.dim.height = 0;
	SDL_SetWindowFullscreen(home->win.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(home->win.window, &editor.dim.width, &editor.dim.height);
	SDL_SetWindowFullscreen(home->win.window, 0);
	SDL_SetWindowSize(home->win.window, editor.dim.width, editor.dim.height);
	SDL_SetWindowPosition(home->win.window, 0, 0);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
	blist = (t_button **)malloc(sizeof(t_button*) * NBR_BUTTONS);
	init_textures(home);
	init_mouse_data(&editor.mouse_data);
	if (!(editor.buffer = (Uint32*)malloc(sizeof(Uint32) *
		(Uint32)editor.dim.width * (Uint32)editor.dim.height)))
		error_output("Memory allocation failed!\n");
	editor.grid_size = 32;
	editor.toggle_grid = 1;
	editor.button_list = create_button_list(blist);
	while (home->game_state == EDITOR)
	{
		editor_events(e, home, &editor);
		draw_ui(&editor);
		draw_buttons(blist, editor.buffer, editor.dim);
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
	// SDL_SetWindowFullscreen(home->win.window, 0);
	SDL_SetWindowSize(home->win.window, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowPosition(home->win.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	home->win.ScreenSurface = SDL_GetWindowSurface(home->win.window);
}