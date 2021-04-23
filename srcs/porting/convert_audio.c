/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_audio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:02:29 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/23 14:13:44 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** typedef struct Mix_Chunk {
** int allocated;
** Uint8 *abuf;
** Uint32 alen;
** Uint8 volume; Per-sample volume, 0-128
** };
** Reading line by line from map data, when we get to audio tag (#AU)
** the line will consist of:
** [Uint8 volume] [Uint32 alen] [Uint8 *abuf]
** load_audio_from_map_data() will always allocate memory
** to abuf buffer (allocated == 1)
** // break character should be consistent on line 35:
** // elems = ft_strsplit(line, ',');
** // line 47 Needs testing:
** // ft_memcpy(audio->abuf, (Uint8)ft_atoi(elems[2]), audio->alen);
*/

Mix_Chunk	*load_audio_from_map_data(char *line)
{
	Mix_Chunk	*audio;
	char		**elems;

	elems = ft_strsplit(line, ',');
	audio = (Mix_Chunk *)malloc(sizeof(Mix_Chunk));
	if (!audio)
		error_output("Memory allocation to Mix_Chunk failed\n");
	audio->volume = (Uint8)ft_atoi(elems[0]);
	audio->alen = (Uint32)ft_atoi(elems[1]);
	audio->abuf = (Uint8 *)malloc(sizeof(Uint8) * audio->alen);
	if (!audio->abuf)
		error_output("Memory allocation of abuf buffer failed\n");
	ft_memcpy(audio->abuf, (Uint8)ft_atoi(elems[2]), audio->alen);
	audio->allocated = 1;
	free_array(elems);
	return (audio);
}
