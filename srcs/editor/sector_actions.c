#include "../../headers/doom_nukem.h"

void	handle_removal(t_editor_sector *sector_list, t_action *action)
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

int		editor_new_sector_wallpoints(t_editor_sector **head,
		t_mouse_data *mouse_data, t_action *action)
{
	t_editor_sector	*temp;

	temp = *head;
	while (temp != NULL && temp->idx_sector != action->selected_sector)
		temp = temp->next;
	if (action->delete)
	{
		handle_removal(temp, action);
		action->delete = 0;
		return (0);
	}
	if (mouse_data->i_mbleft)
	{
		if (add_point_to_list(temp, mouse_data, action) == 3)
			return (1);
	}
	mouse_data->i_mbleft = 0;
	return (0);
}

int		get_sector_count(t_editor_sector **list)
{
	t_editor_sector	*temp;
	unsigned int	i;

	temp = *list;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	reset_sector_indexes(t_editor_sector **head)
{
	t_editor_sector	*temp;
	int				idx;
	int				nbr_of_sectors;

	nbr_of_sectors = get_sector_count(head);
	temp = *head;
	idx = 0;
	while (idx < nbr_of_sectors)
	{
		temp->idx_sector = idx;
		temp = temp->next;
		idx++;
	}
}

// void	delete_entities_from_sector(t_entity_list **entity_head, int sector_idx, t_action *action)
// {
// 	t_entity_list	*temp;
// 	t_entity_list	*prev;
// 	int				nbr_of_entities;
// 	int				i;
// 	int				nbr_to_delete;

// 	i = 0;
// 	nbr_to_delete = 0;
// 	nbr_of_entities = get_entity_count(entity_head);
// 	temp = *entity_head;
// 	while (i < nbr_of_entities && temp != NULL)
// 	{
// 		if (temp->sector_idx == sector_idx)
// 			nbr_to_delete++;
// 		i++;
// 		temp = temp->next;
// 	}
// }

void	editor_free_selected_sector(t_editor_sector **head, t_entity_list **entity_head, t_action *action)
{
	t_editor_sector	*temp;
	t_editor_sector	*prev;

	temp = *head;
	(void)entity_head;
	if (temp == NULL)
		return ;
	if (temp != NULL && temp->idx_sector == action->selected_sector)
	{
		*head = temp->next;
		// delete_entities_from_sector(entity_head, temp->idx_sector, action);
		editor_free_walls(&temp->walls, temp->nb_of_walls);
		free(temp);
		reset_sector_indexes(head);
		action->delete = 0;
		action->selected_sector = -1;
		return ;
	}
	while (temp != NULL && temp->idx_sector != action->selected_sector)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	// delete_entities_from_sector(entity_head, temp->idx_sector, action);
	editor_free_walls(&temp->walls, temp->nb_of_walls);
	free(temp);
	reset_sector_indexes(head);
	action->delete = 0;
	action->selected_sector = -1;
}
