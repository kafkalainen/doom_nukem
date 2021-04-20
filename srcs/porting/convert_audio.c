/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_audio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:02:29 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/02 13:57:40 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

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
** load_audio_from_map_data() will always allocate memory to abuf buffer (allocated == 1)
*/

Mix_Chunk	*load_audio_from_map_data(char *line)
{
	Mix_Chunk	*audio;
	char		**elems;

	elems = ft_strsplit(line, ','); // break character should be consistent throughout map data
	if (!(audio = (Mix_Chunk *)malloc(sizeof(Mix_Chunk))))
		error_output("Memory allocation to Mix_Chunk failed\n");
	audio->volume = (Uint8)ft_atoi(elems[0]);
	audio->alen = (Uint32)ft_atoi(elems[1]);
	if (!(audio->abuf = (Uint8 *)malloc(sizeof(Uint8) * audio->alen)))
		error_output("Memory allocation of abuf buffer failed\n");
	ft_memcpy(audio->abuf, (Uint8)ft_atoi(elems[2]), audio->alen); // needs testing
	audio->allocated = 1;
	free_array(elems);
	return (audio);
}
