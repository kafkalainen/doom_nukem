/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:03:47 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/28 13:03:38 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Reading the map data into sector structs [and loading PNG and WAV files
** into memory for later use. (included later)]
*/

#include "../../doom_nukem.h"

static void			store_polygons(char *line, int numwalls, t_sector *sect)
{
	t_polygon	*new;
	t_polygon	*temp;
	t_xy		pos;
	int			texid;


	temp = sect->polygons;
	while (numwalls > 0)
	{
		pos.x = ft_atoi(line);
		pos.y = ft_atoi(line + 1 + ft_numlen(pos.x));
		texid = ft_atoi(line + 2 + ft_numlen(pos.x) + ft_numlen(pos.y));
		new = new_polygon(pos, texid);
		temp->next = new;
		temp = temp->next;
		line += 3 + ft_numlen(pos.x) + ft_numlen(pos.y) + ft_numlen(texid);
		numwalls--;
	}
	new = new_polygon(sect->polygons->next->x0, ft_atoi(line));
	temp->next = new;
	temp = temp->next;
}

t_sector			new_sector(char *line)
{
	t_sector	sect;
	t_sector	temp;

	sect.polygons = (t_polygon*)malloc(sizeof(*sect.polygons));
	temp.polygons = sect.polygons;
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	sect.nb_of_walls = ft_atoi(line);
	line += 1 + ft_numlen(sect.nb_of_walls);
	sect.ground = ft_atoi(line);
	line += 1 + ft_numlen(sect.ground);
	sect.ceiling = ft_atoi(line);
	line += 1 + ft_numlen(sect.ceiling);
	sect.tex_floor = ft_atoi(line);
	line += 1 + ft_numlen(sect.tex_floor);
	sect.tex_ceil = ft_atoi(line);
	line += 1 + ft_numlen(sect.tex_ceil);
	store_polygons(line, sect.nb_of_walls, &sect);
	sect.polygons = sect.polygons->next;
	sect.polygons = temp.polygons;
	return sect;
}
