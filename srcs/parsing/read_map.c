/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:03:47 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/25 11:03:47 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Reading the map data into sector structs [and loading PNG and WAV files
** into memory for later use. (included later)]
*/

#include "../../doom_nukem.h"

t_sector		new_sector(char *line)
{
	t_sector	sec;
	int			numwalls;

	numwalls = atoi(line);
	line += 2;
	sec.ground = ft_atoi("4 asd");
	printf("Walls: %d    Z: %f\n", numwalls, sec.ground);
	return sec;
}
