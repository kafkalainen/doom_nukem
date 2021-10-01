/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sector_data2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:56:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/01 11:51:14 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_uchar	*get_writable_wall_data(t_editor_walls *wall)
{
	t_uchar	*buf;

	buf = (t_uchar *)ft_strjoin_freeable(WRITE_BREAKER,
			ft_itoa(wall->x0.x), 0, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(wall->x0.y), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(wall->type), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa((int)wall->height.ground), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa((int)wall->height.ceiling), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}

t_uchar	*write_plot_lines(t_uchar *plot)
{
	char			**strings;
	t_uchar	*buf;
	int				i;
	int				lines;

	lines = get_nbr_of_lines(plot);
	buf = (t_uchar *)ft_strjoin_freeable("#",
			(char *)ft_itoa(lines), 0, 1);
	strings = ft_strsplit((const char *)plot, '\n');
	i = 0;
	if (strings)
	{
		while (i < lines)
		{
			buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
					WRITE_BREAKER, 1, 0);
			buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
					strings[i], 1, 1);
			i++;
		}
		free(strings);
	}
	return (buf);
}

t_uchar	*get_sector_plot(t_uchar *plot)
{
	t_uchar	*buf;

	if (plot == NULL)
		buf = (t_uchar *)ft_strjoin_freeable("#", "0", 0, 0);
	else
		buf = write_plot_lines(plot);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, "\n", 1, 0);
	return (buf);
}

t_uchar	*get_writable_sector_header_data(t_editor_sector *sector,
	t_uchar *buf)
{
	buf = (t_uchar *)ft_strjoin_freeable(WRITE_BREAKER, "sector", 0, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->idx_sector), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->nb_of_walls), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->tex_floor), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->tex_ceil), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->is_elevator), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->gravity), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}

t_uchar	*get_writable_light_data(t_editor_sector *sector,
	t_uchar *buf)
{
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.pos.x), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.pos.y), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.intensity), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.state), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf, WRITE_BREAKER, 1, 0);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.is_linked), 1, 1);
	buf = (t_uchar *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}
