/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sector_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 16:47:49 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/01 14:02:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uchar	*get_writable_sector_data(t_editor_sector *sector)
{
	t_uchar			*buf;
	int				i;
	t_editor_walls	*wall;

	buf = NULL;
	buf = get_writable_sector_header_data(sector, buf);
	i = 0;
	wall = sector->walls;
	while (i < sector->nb_of_walls)
	{
		buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
				(char *)get_writable_wall_data(wall), 1, 1);
		wall = wall->next;
		i++;
	}
	buf = get_writable_light_data(sector, buf);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			(char *)get_sector_plot(sector->plot_line), 1, 1);
	return (buf);
}

t_uchar	*write_map_header(int nbr_of_sectors,
	int end_sector, int linked_map,
		t_uchar *linked_map_name)
{
	t_uchar	*buf;

	buf = (t_uchar *)ft_strjoin_freeable("#doom_nukem_sectors#",
			ft_itoa(nbr_of_sectors), 0, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(end_sector), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(linked_map), 1, 1);
	if (linked_map)
	{
		buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
				WRITE_BREAKER, 1, 0);
		buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
				(char *)linked_map_name, 1, 0);
	}
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, "\n", 1, 0);
	return (buf);
}

char	*get_player_start(t_plr_pos plr)
{
	char	*buf;

	buf = ft_strjoin_freeable(WRITE_BREAKER, ft_itoa(plr.x), 0, 1);
	buf = ft_strjoin_freeable(buf, WRITE_BREAKER, 1, 0);
	buf = ft_strjoin_freeable(buf, ft_itoa(plr.z), 1, 1);
	buf = ft_strjoin_freeable(buf, WRITE_BREAKER, 1, 0);
	buf = ft_strjoin_freeable(buf, ft_itoa(plr.sector), 1, 1);
	buf = ft_strjoin_freeable(buf, "\n", 1, 0);
	return (buf);
}

void	write_sector_data(int *fd,
	t_editor *editor)
{
	int				nbr_of_sectors;
	t_editor_sector	*temp;
	t_uchar			*buf;
	int				i;

	i = check_if_linked(editor->linked_mapname);
	buf = NULL;
	nbr_of_sectors = get_nbr_of_sectors(&editor->sector_list);
	buf = write_map_header(nbr_of_sectors, editor->end_sector.sector,
			i, editor->linked_mapname);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			get_player_start(editor->plr), 1, 1);
	if (doom_write(fd, (const void **)&buf, ft_strlen((const char *)buf)) == -1)
		error_output("ERROR: Failed to add sector numbers.");
	ft_strdel((char **)&buf);
	temp = editor->sector_list;
	while (temp != NULL)
	{
		buf = get_writable_sector_data(temp);
		if (doom_write(fd, (const void **)&buf,
				ft_strlen((const char *)buf)) == -1)
			error_output("ERROR: Failed to add sector data.");
		ft_strdel((char **)&buf);
		temp = temp->next;
	}
}
