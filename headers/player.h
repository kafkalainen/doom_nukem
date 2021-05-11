/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/05/07 16:05:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_input
{
	int				right;
	int				left;
	int				up;
	int				down;
	int				rot_right;
	int				rot_left;
	int				crouch;
	int				wireframe;
	int				minimap;
	int				info;
	int				quit;
	int				mouse;
}					t_input;

typedef struct s_player
{
	float			pitch;
	float			z;
	float			height;
	float			angle;
	float			acceleration;
	int				gravity;
	int				current_sector;
	t_xy			pos;
	t_xy			dir;
	t_xy			move_dir;
	t_input			input;
	Uint32			time;
	t_audio			audio;
}					t_player;

enum e_movement
{
	open_space = -9999
};

#endif
