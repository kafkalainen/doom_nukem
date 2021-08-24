/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:12:34 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/24 11:45:43 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	rotate_based_on_axes(t_bullet_hole *hole, t_projectile *current)
{
	float	angle[3];
	t_m4x4	x;
	t_m4x4	y;
	t_m4x4	z;
	t_m4x4	combined;

	angle[0] = vec3_ang_axis(current->normal, hole->normal, 'x');
	angle[1] = vec3_ang_axis(current->normal, hole->normal, 'y');
	angle[2] = vec3_ang_axis(current->normal, hole->normal, 'z');
	x = rotation_matrix_x(angle[0]);
	y = rotation_matrix_y(angle[1]);
	z = rotation_matrix_z(angle[2]);
	combined = multiply_matrix(&z, &y);
	combined = multiply_matrix(&combined, &x);
	current->top.p[0] = multi_vec_matrix(&current->top.p[0], &combined);
	current->top.p[1] = multi_vec_matrix(&current->top.p[1], &combined);
	current->top.p[2] = multi_vec_matrix(&current->top.p[2], &combined);
	current->bot.p[0] = multi_vec_matrix(&current->bot.p[0], &combined);
	current->bot.p[1] = multi_vec_matrix(&current->bot.p[1], &combined);
	current->bot.p[2] = multi_vec_matrix(&current->bot.p[2], &combined);
}

static void	set_bullet_hole(t_bullet_hole *hole, t_projectile *current)
{
	if (hole->hole_type != nothing)
	{
		current->pos = hole->point;
		rotate_based_on_axes(hole, current);
		current->top.normal = hole->normal;
		current->bot.normal = hole->normal;
		current->sector_idx = hole->sector_idx;
		printf("%d\n", current->sector_idx);
	}
}

void	shooting_handle(t_home *home, t_player *plr)
{
	t_bullet_hole	hole;
	t_projectile	*current;

	if (home->projectile_idx >= MAX_PROJECTILES - 1)
		home->projectile_idx = -1;
	if (home->nbr_of_projectiles < MAX_PROJECTILES)
		home->nbr_of_projectiles++;
	home->projectile_idx++;
	hole = get_bullet_hit_point(home, plr, plr->cur_sector);
	current = home->projectile_pool[home->projectile_idx];
	initialize_projectile_triangles(current);
	set_bullet_hole(&hole, current);
}
