/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sector_data2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:56:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/09 11:32:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

unsigned char	*get_writable_wall_data(t_editor_walls *wall)
{
	unsigned char	*buf;

	buf = (unsigned char *)ft_strjoin_freeable(WRITE_BREAKER,
			ft_itoa(wall->x0.x), 0, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(wall->x0.y), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(wall->type), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa((int)wall->height.ground), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa((int)wall->height.ceiling), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}

unsigned char	*write_plot_lines(unsigned char *plot)
{
	char			**strings;
	unsigned char	*buf;
	int				i;
	int				lines;

	lines = get_nbr_of_lines(plot);
	buf = (unsigned char *)ft_strjoin_freeable("#",
			(char *)ft_itoa(lines), 0, 1);
	strings = ft_strsplit((const char *)plot, '\n');
	i = 0;
	if (strings)
	{
		while (i < lines)
		{
			buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
					WRITE_BREAKER, 1, 0);
			buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
					strings[i], 1, 1);
			i++;
		}
		free(strings);
	}
	return (buf);
}

unsigned char	*get_sector_plot(unsigned char *plot)
{
	unsigned char	*buf;

	if (plot == NULL)
		buf = (unsigned char *)ft_strjoin_freeable("#", "0", 0, 0);
	else
		buf = write_plot_lines(plot);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf, "\n", 1, 0);
	return (buf);
}

unsigned char	*get_writable_sector_data2(t_sector_list *sector,
	unsigned char *buf)
{
	buf = (unsigned char *)ft_strjoin_freeable(WRITE_BREAKER,
			"sector", 0, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->idx_sector), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->nb_of_walls), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->tex_floor), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->tex_ceil), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->is_elevator), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}

unsigned char	*get_writable_sector_data3(t_sector_list *sector,
	unsigned char *buf)
{
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.pos.x), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.pos.y), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.intensity), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.is_linked), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(sector->light.state), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			"\n", 1, 0);
	return (buf);
}
