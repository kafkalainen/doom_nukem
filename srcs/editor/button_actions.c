#include "../headers/doom_nukem.h"

void		main_button_actions(t_action *action, int i)
{
	if (i == 0)
	{
		action->save_file = 1;
		printf("save file\n");
		if (!action->map_name_set)
		{
			printf("input active\n");
			action->input_active = 1;
		}
	}
	else if (i == 1 && action->nbr_of_maps > 0)
		action->open_file = 1;
	else if (i == 2)
	{
		if (action->grid)
			action->grid = 0;
		else
			action->grid = 1;
	}
	else if (i == 3)
	{
		if (!action->create_sector)
			action->create_sector = 1;
	}
	else if (i == 4)
		action->assign_end_sector = 1;
	else if (i == 5  && action->nbr_of_maps > 0)
		action->link_maps = 1;
	else if (i == 6)
		action->unlink_maps = 1;
	else if (i == 7)
		action->assign_player_start = 1;
	else if (i == 8)
		action->create_elevator = 1;
}

void	entity_button_actions(t_action *action, int i)
{
	action->edit_entity = 1;
	if (i == 21)
		action->change_entity_type = 1;
	else if (i == 22)
		action->toggle_entity_is_linked = 1;
	else if (i == 23)
		action->toggle_is_revealed = 1;
	else if (i == 24)
		action->toggle_is_static = 1;
	else if (i == 25)
		action->toggle_state = 1;
}

int		check_bbox(t_xy start, t_xy end, int mouse_x, int mouse_y)
{
	if (start.x <= mouse_x && start.y <= mouse_y &&
		end.x >= mouse_x && end.y >= mouse_y)
		return (TRUE);
	else
		return (FALSE);
}
