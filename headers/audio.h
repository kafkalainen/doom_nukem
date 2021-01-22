/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:35:03 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/22 14:01:57 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AUDIO_H
# define AUDIO_H

typedef struct	s_audio
{
	Mix_Music	*music;
	Mix_Chunk	*footstep;
}				t_audio;
#endif
