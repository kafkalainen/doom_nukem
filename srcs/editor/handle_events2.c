/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:09:30 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/15 18:45:34 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	link_maps(t_action *action, unsigned char **linked_mapname,
		char **map_names)
{
	if (*linked_mapname)
	{
		free(*linked_mapname);
		*linked_mapname = NULL;
	}
	*linked_mapname = (unsigned char *)ft_strjoin("./map_files/",
			map_names[action->option]);
	action->link_maps = 0;
	action->option = 0;
	action->start = 0;
}

int	check_plr_start_and_end_sector_exists(t_editor_sector **list,
	t_plr_pos plr, int end_sector)
{
	t_editor_sector	*temp;
	t_editor_sector	*temp_two;

	temp = *list;
	temp_two = *list;
	while (temp != NULL && temp->idx_sector != plr.sector)
		temp = temp->next;
	if (temp == NULL)
		return (FALSE);
	if (!check_bbox(temp->bbox.start, temp->bbox.end, vec2(plr.x, plr.z)))
		return (FALSE);
	while (temp_two != NULL && temp_two->idx_sector != end_sector)
		temp_two = temp_two->next;
	if (temp_two == NULL)
		return (FALSE);
	return (TRUE);
}

void	assign_end_sector(t_editor_sector **list, t_xy *click, int *end_sector,
		int *sector_assigned)
{
	t_editor_sector	*temp;

	temp = *list;
	while (temp != NULL && !check_bbox(temp->bbox.start, temp->bbox.end,
			*click))
		temp = temp->next;
	if (temp == NULL)
		return ;
	*end_sector = temp->idx_sector;
	*sector_assigned = 0;
}

int	assign_player_start(t_editor_sector **list, t_xy *click, t_plr_pos *plr,
	int *assign_player_start)
{
	t_editor_sector	*temp;

	temp = *list;
	while (temp != NULL && !check_bbox(temp->bbox.start, temp->bbox.end,
			*click))
		temp = temp->next;
	if (temp == NULL)
		return (FALSE);
	plr->sector = temp->idx_sector;
	plr->x = temp->centroid.x;
	plr->z = temp->centroid.y;
	*assign_player_start = 0;
	return (TRUE);
}
