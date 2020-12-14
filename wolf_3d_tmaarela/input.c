/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 05:21:14 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 18:12:35 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	player_rotate(double delta_time, t_kboard *key, t_me *me)
{
	if (key->e)
		me->dir = vec2_rot(me->dir, 60 * DEG_TO_RAD * delta_time);
	if (key->q)
		me->dir = vec2_rot(me->dir, -60 * DEG_TO_RAD * delta_time);
	if (key->space)
		me->height += 1 * delta_time;
	if (key->ctrl)
		me->height += -1 * delta_time;
}

void	player_move(double delta_time, t_kboard *key, t_me *me, t_map *map)
{
	t_xy pos;
	t_xy dir;

	if (key->up)
	{
		pos = vec2_add(me->pos, vec2_mul(me->dir, 4 * delta_time));
		me->pos = (valid_location(pos, map)) ? pos : me->pos;
	}
	if (key->down)
	{
		pos = vec2_dec(me->pos, vec2_mul(me->dir, 4 * delta_time));
		me->pos = (valid_location(pos, map)) ? pos : me->pos;
	}
	if (key->left)
	{
		dir = vec2_rot(me->dir, 90.0 * DEG_TO_RAD);
		pos = vec2_dec(me->pos, vec2_mul(dir, 4 * delta_time));
		me->pos = (valid_location(pos, map)) ? pos : me->pos;
	}
	if (key->right)
	{
		dir = vec2_rot(me->dir, 90.0 * DEG_TO_RAD);
		pos = vec2_add(me->pos, vec2_mul(dir, 4 * delta_time));
		me->pos = (valid_location(pos, map)) ? pos : me->pos;
	}
}

int		valid_location(t_xy pos, t_map *map)
{
	return ((((int)pos.x > 0) && ((int)pos.x < map->size.x))
		&& (((int)pos.y > 0) && ((int)pos.y < map->size.y))
		&& (map->data[(int)pos.y][(int)pos.x] != '#'));
}
