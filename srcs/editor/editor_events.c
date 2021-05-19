#include "../headers/doom_nukem.h"

void	editor_mouse(t_mouse_data *mouse_data, SDL_Event *e)
{

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT || mouse_data->i_mbleft == 1)
		{
			mouse_data->i_mbleft = 1;
			mouse_data->x = e->motion.x;
			mouse_data->y = e->motion.y;
		}
		if (e->button.button == SDL_BUTTON_RIGHT)
		{
			mouse_data->i_mbright = 1;
			mouse_data->x = e->motion.x;
			mouse_data->y = e->motion.y;
		}
	}
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (e->button.button == SDL_BUTTON_LEFT )
			mouse_data->i_mbleft = 0;
		if (e->button.button == SDL_BUTTON_RIGHT)
			mouse_data->i_mbright = 0;
	} 
}

int		check_bbox(t_xy start, t_xy end, int mouse_x, int mouse_y)
{
	if (start.x < mouse_x && start.y < mouse_y && 
		end.x > mouse_x && end.y > mouse_y)
		return (1);
	else 
		return (0);
}

void	check_event(t_mouse_data *mouse_data, t_button **list)
{
	int	i;

	i = 0;
	while(i < NBR_BUTTONS)
	{
		if (check_bbox(list[i]->ltop, list[i]->wh, mouse_data->x, mouse_data->y))
			mouse_data->selected = i;
	}
	if (mouse_data->selected == 0)
		printf("%s\n", "painoit nappula nro 0");
	if (mouse_data->selected == 1)
		printf("%s\n", "painoit nappula nro 1");
	if (mouse_data->selected == 2)
		printf("%s\n", "painoit nappula nro 2");
	if (mouse_data->selected == 3)
		printf("%s\n", "painoit nappula nro 3");
}

void	editor_events(SDL_Event *e, t_home *home, t_editor *editor)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			editor_mouse(editor->mouse_data, e);
			check_event(editor->mouse_data, editor->button_list);
		}
		if (e->type == SDL_MOUSEBUTTONUP)
			check_event(editor->mouse_data, editor->button_list);
		if (e->type == SDL_QUIT)
			home->game_state = QUIT;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			home->game_state = MAIN_MENU;
	}
}
