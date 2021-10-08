/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_projectiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:07:21 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 12:35:19 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	rotate_moving_projectile(t_projectile *current, t_player *plr)
{
	float	angle[3];
	t_m4x4	y;
	t_m4x4	combined;
	t_xyz	vec_to_plr;

	vec_to_plr = vec3_unit_vector(vec3_dec(plr->pos, current->pos));
	angle[1] = vec3_ang_axis(current->top.normal, vec_to_plr, 'y');
	y = rotation_matrix_y(angle[1]);
	combined = y;
	current->top.p[0] = multi_vec_matrix(&current->top.p[0], &combined);
	current->top.p[1] = multi_vec_matrix(&current->top.p[1], &combined);
	current->top.p[2] = multi_vec_matrix(&current->top.p[2], &combined);
	current->bot.p[0] = multi_vec_matrix(&current->bot.p[0], &combined);
	current->bot.p[1] = multi_vec_matrix(&current->bot.p[1], &combined);
	current->bot.p[2] = multi_vec_matrix(&current->bot.p[2], &combined);
	current->top.normal = vec_to_plr;
	current->bot.normal = vec_to_plr;
}

t_bool	projectile_movement(t_home *home, t_player *plr, t_projectile *current,
		Uint32 t)
{
	t_wall	*wall;
	float	dist;
	t_xyz	test_pos;

	current->move_dir = vec3_unit_vector(current->move_dir);
	test_pos = vec3_add(current->pos, vec3_mul(current->move_dir,
				t * current->velocity));
	if (get_distance_squared(current->pos, plr->pos) < 0.1f * 0.1f)
		return (false);
	if (check_distance_to_ceiling(home->sectors[current->sector_idx],
			&test_pos))
		return (false);
	wall = check_if_too_close_to_walls(home->sectors[current->sector_idx],
			0.1f, test_pos, current->move_dir);
	if (!wall)
	{
		current->pos = test_pos;
		check_if_moved_through_portal(&current->sector_idx, current->pos,
			1.0f, home);
		check_distance_to_ground(home->sectors[current->sector_idx],
			0.1f, current->pos, &dist);
		if (dist > 0.1f)
			return (true);
	}
	return (false);
}

static void	initialize_trajectory(t_ray *trajectory,
	t_projectile *projectile, t_player *plr)
{
	trajectory->side = ENEMY;
	trajectory->start_sector = projectile->sector_idx;
	trajectory->end_sector = plr->cur_sector;
	trajectory->pos = projectile->pos;
	trajectory->dir = projectile->move_dir;
	trajectory->plr_pos = plr->pos;
}

static void	update_projectile(t_projectile *current, t_home *home,
			t_player *plr, Uint32 t)
{
	t_ray			trajectory;
	t_bullet_hole	hole;

	initialize_projectile_triangles(current);
	rotate_moving_projectile(current, plr);
	if (!projectile_movement(home, plr, current, t))
	{
		initialize_trajectory(&trajectory, current, plr);
		hole = get_bullet_hit_point(home, &trajectory,
				trajectory.start_sector);
		if (hole.type == player)
			player_take_damage(plr, 2, t);
		current->is_active = false;
		initialize_projectile_triangles(current);
		set_bullet_hole(&hole, current);
	}
}

void	update_projectiles(t_home *home, t_player *plr, Uint32 t)
{
	Uint32			i;
	t_projectile	*current;

	i = 0;
	while (i < home->nbr_of_projectiles)
	{
		current = home->projectile_pool[i];
		if (current->is_active)
		{
			update_projectile(current, home, plr, t);
		}
		i++;
	}
}
