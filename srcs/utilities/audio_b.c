/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:34:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/07/06 14:40:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_audio_to_null(t_audio *audio)
{
	audio->footstep1 = NULL;
	audio->footstep2 = NULL;
	audio->music = NULL;
}
