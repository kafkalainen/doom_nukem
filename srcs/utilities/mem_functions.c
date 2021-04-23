/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:50:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/23 14:50:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** 1st pass at loading char* and converting back to t_texture.
** Need to see text output before making further changes
*/

void	free_array(unsigned char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_strdel((char**)&array[i]);
		i++;
	}
	free(array);
}
