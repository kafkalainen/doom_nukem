/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/29 16:26:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct		s_input
{
	int				right;
	int				left;
	int				up;
	int				down;
	int				z;
	int				x;
}					t_input;

typedef struct		s_player
{
	t_xy			pos;
	t_xy			dir;
	float			pitch;
	float			z;
	float			height;
	t_input			input;
	clock_t			time;
	t_audio			audio;
	float			angle;
	int				current_sector;
}					t_player;

#endif
