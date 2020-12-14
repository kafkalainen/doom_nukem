/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 00:13:34 by ngontjar          #+#    #+#             */
/*   Updated: 2020/10/14 16:19:27 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				keyboard_press(int keycode, t_kboard *key)
{
	if (keycode == vk_up)
		key->up = 1;
	if (keycode == vk_left)
		key->left = 1;
	if (keycode == vk_right)
		key->right = 1;
	if (keycode == vk_down)
		key->down = 1;
	if (keycode == ord_q)
		key->q = 1;
	if (keycode == ord_e)
		key->e = 1;
	if (keycode == ord_space)
		key->space = 1;
	if (keycode == ord_ctrl)
		key->ctrl = 1;
	if (keycode == vk_esc)
		exit(0);
	return (1);
}

int				keyboard_release(int keycode, t_kboard *key)
{
	if (keycode == vk_up)
		key->up = 0;
	if (keycode == vk_left)
		key->left = 0;
	if (keycode == vk_right)
		key->right = 0;
	if (keycode == vk_down)
		key->down = 0;
	if (keycode == ord_q)
		key->q = 0;
	if (keycode == ord_e)
		key->e = 0;
	if (keycode == ord_space)
		key->space = 0;
	if (keycode == ord_ctrl)
		key->ctrl = 0;
	return (1);
}

int				mouse_move(int x, int y, t_prog *p)
{
	p->mouse.delta = vec2(x - p->mouse.pos.x, y - p->mouse.pos.y);
	p->mouse.pos = vec2(x, y);
	p->me.height = 1 - ft_map(p->mouse.pos.y, vec2(0, WIN_HEIGHT), vec2(0, 1));
	p->me.dir = vec2_rot(p->me.dir, p->mouse.delta.x * M_SENS * DEG_TO_RAD);
	return (TRUE);
}

int				movement(t_prog *p)
{
	clock_t	time;
	double	delta_time;

	time = clock();
	delta_time = ((time - p->time) / (double)CLOCKS_PER_SEC);
	if (delta_time < 0.0166667)
		return (1);
	p->time = time;
	player_rotate(delta_time, &p->key, &p->me);
	player_move(delta_time, &p->key, &p->me, &p->map);
	render(p);
	return (1);
}

int				window_close(t_prog *p)
{
	(void)p;
	exit(0);
}
