/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edit_sector2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:14:41 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/23 10:23:42 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	update_sector_light_values(t_editor_sector *sector,
		t_entity_list **head)
{
	t_entity_list	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->sector_idx == sector->idx_sector && temp->entity_type == lamp)
		{
			sector->light.pos.x = temp->pos.x;
			sector->light.pos.y = temp->pos.z;
			sector->light.state = temp->state;
			sector->light.intensity = 30;
			break ;
		}
		temp = temp->next;
	}
}

void	editor_set_all_sector_floor_heights(t_editor_sector *sector,
	unsigned char **int_string)
{
	int				floor_height;
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	floor_height = ft_atoi((const char *)*int_string);
	if (floor_height > 99)
		floor_height = 99;
	if (floor_height < -99)
		floor_height = -99;
	free(*int_string);
	*int_string = NULL;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ceiling > floor_height)
			wall->height.ground = floor_height;
		wall = wall->next;
		i++;
	}
}

void	editor_set_all_sector_ceiling_heights(t_editor_sector *sector,
	unsigned char **int_string)
{
	int				ceiling_height;
	t_editor_walls	*wall;
	int				i;

	i = 0;
	wall = sector->walls;
	ceiling_height = ft_atoi((const char *)*int_string);
	if (ceiling_height > 99)
		ceiling_height = 99;
	if (ceiling_height < -99)
		ceiling_height = -99;
	free(*int_string);
	*int_string = NULL;
	while (i < sector->nb_of_walls)
	{
		if (wall->height.ground < ceiling_height)
			wall->height.ceiling = ceiling_height;
		wall = wall->next;
		i++;
	}
}

void	editor_edit_change_sector_ceiling_tex(t_editor *editor)
{
	if (editor->temp_sector->tex_ceil == -surf0)
		editor->temp_sector->tex_ceil = -surf1;
	else if (editor->temp_sector->tex_ceil == -surf1)
		editor->temp_sector->tex_ceil = -surf2;
	else if (editor->temp_sector->tex_ceil == -surf2)
		editor->temp_sector->tex_ceil = -surf3;
	else if (editor->temp_sector->tex_ceil == -surf3)
		editor->temp_sector->tex_ceil = -surf4;
	else if (editor->temp_sector->tex_ceil == -surf4)
		editor->temp_sector->tex_ceil = -surf5;
	else if (editor->temp_sector->tex_ceil == -surf5)
		editor->temp_sector->tex_ceil = -surf6;
	else if (editor->temp_sector->tex_ceil == -surf6)
		editor->temp_sector->tex_ceil = -surf7;
	else if (editor->temp_sector->tex_ceil == -surf7)
		editor->temp_sector->tex_ceil = -surf8;
	else if (editor->temp_sector->tex_ceil == -surf8)
		editor->temp_sector->tex_ceil = -surf9;
	else if (editor->temp_sector->tex_ceil == -surf9)
		editor->temp_sector->tex_ceil = -surf0;
	editor->action.change_ceiling_texture = 0;
	editor->action.edit_sector = 0;
}
