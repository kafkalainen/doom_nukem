/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/14 13:56:19 by jnivala          ###   ########.fr       */
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
	int				jump;
	int				wireframe;
	int				minimap;
	int				info;
	int				mouse;
	int				debug_up;
	int				debug_down;
	int				debug_left;
	int				debug_right;
}					t_input;

typedef struct s_player
{
	t_input			input;
	t_xyz			pos;
	t_xyz			look_dir;
	t_xyz			move_dir;
	t_xyz			target;
	t_xyz			up;
	t_xy			dir;
	float			yaw;
	float			pitch;
	float			height;
	float			acceleration;
	int				cur_sector;
	Uint32			gravity_pull;
	Uint32			time;
	t_audio			audio;
}					t_player;

enum e_movement
{
	open_space = -9999
};

#endif
