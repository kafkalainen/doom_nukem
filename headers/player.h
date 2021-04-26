/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:36:51 by tmaarela          #+#    #+#             */
/*   Updated: 2021/04/26 15:47:53 by jnivala          ###   ########.fr       */
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
	int				wireframe;
	int				minimap;
	int				info;
	int				quit;
	int				mouse;
}					t_input;

typedef struct s_player
{
	t_xy			pos;
	t_xy			dir;
	t_xy			move_dir;
	float			pitch;
	float			z;
	float			height;
	t_input			input;
	clock_t			time;
	t_audio			audio;
	float			angle;
	int				current_sector;
}					t_player;

enum e_movement
{
	open_space = -9999
};

#endif
