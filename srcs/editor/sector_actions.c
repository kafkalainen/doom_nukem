#include "../../headers/doom_nukem.h"

void	create_new_sector(t_sector_list **head, t_action *action)
{
	t_sector_list	*temp;
	t_sector_list	*new;

	new = (t_sector_list*)malloc(sizeof(t_sector_list));
	if (!new)
		error_output("Memory allocation of sector failed\n");
	new->bbox.start = vec2(0, 0);
	new->bbox.end = vec2((0), (0));
	new->nb_of_walls = 0;
	new->tex_ceil = 0;
	new->tex_floor = 0;
	new->light.pos.x = 0;
	new->light.pos.y = 0;
	new->has_light_button = 0;
	new->has_light_source = 0;
	new->light.intensity = 0;
	new->light.is_linked = 0;
	new->light.state = 0;
	new->idx_sector = 0;
	if (action->create_elev_button)
		new->is_elevator = 1;
	else
		new->is_elevator = 0;
	new->sector_plot = NULL;
	new->walls = NULL;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			new->idx_sector++;
			temp = temp->next;
		}
		new->idx_sector++;
		temp->next = new;
		new->next = NULL;
	}
	action->selected_sector = new->idx_sector;
}

void	handle_removal(t_sector_list *sector_list, t_action *action)
{
	t_editor_walls *temp;

	temp = sector_list->walls;
	printf("in handle_removal\n");
	if (sector_list->nb_of_walls == 1)
		return ;
	while (temp && sector_list->nb_of_walls > action->selected_point)
	{
		printf("selected point %d nb_of walls is %d\n", action->selected_point, sector_list->nb_of_walls);
		remove_last_point(&temp, &sector_list->nb_of_walls, action->selected_point);
	}
	action->selected_point -= 1;
}

void	editor_free_walls(t_editor_walls **head, int nbr_of_walls)
{
	t_editor_walls	*item;

	while (nbr_of_walls--)
	{
		item = *head;
		*head = item->next;
		free(item);
		item = NULL;
	}
}

void	editor_free_sector(t_sector_list **head)
{
	if (!*head)
		return ;
	editor_free_walls(&(*head)->walls, (*head)->nb_of_walls);
	free(*head);
	*head = NULL;
}

void	editor_free_selected_sector(t_editor *editor, int idx)
{
	t_sector_list	*selected;
	t_sector_list	*temp;

	printf("idx: %d\n", idx);
	if (!editor || !editor->sector_list)
		return ;
	temp = editor->sector_list;
	while (temp->idx_sector < idx)
		temp = temp->next;
	if (idx == 0) {
		selected = temp;
		selected->next = NULL;
		free(selected);
		selected = NULL;
	}
	else
		selected = temp->next;
	editor_free_walls(&selected->walls, selected->nb_of_walls);
	editor->action.selected_sector = -1;

	//t_sector_list	*previous;
	//t_sector_list	*deleted;
	//t_sector_list	*next;
//
	//if (!editor && !editor->sector_list)
	//	return ;
	//previous = editor->sector_list;
	//while (previous != NULL && previous->next != NULL
	//	&& previous->next->idx_sector != selected)
	//	previous = previous->next;
	//deleted = previous->next;
	//if (deleted)
	//{
	//	next = deleted->next;
	//	editor_free_walls(&deleted->walls, deleted->nb_of_walls);
	//	free(deleted);
	//	deleted = NULL;
	//	previous->next = next;
	//}
}

int		handle_sector(t_sector_list **head, t_mouse_data *mouse_data, t_action *action)
{
	t_sector_list	*temp;

	temp = *head;
	while (temp != NULL && temp->idx_sector != action->selected_sector)
		temp = temp->next;
	printf("sectors_created_2: %d\n", temp->idx_sector);
	if (action->edit_sector && action->delete)
	{
		handle_removal(temp, action);
		action->delete = 0;
		printf("out of handle removal \n");
		return (0);
	}
	if (action->edit_sector && mouse_data->i_mbleft)
	{
		if (add_point_to_list(temp, mouse_data, action) == 3)
			return (1);
	}
	if (action->selected_sector >= 0 && action->input_active == 14)
		edit_story(temp, action);
	mouse_data->i_mbleft = 0;
	return (0);
}
