/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:48:43 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/26 08:42:59 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	initialize_player_triangles(t_player *plr, t_xyz enemy_dir)
{
	float	angle[3];
	t_m4x4	x;
	t_m4x4	y;
	t_m4x4	z;
	t_m4x4	combined;

	angle[0] = vec3_ang_axis(plr->move_dir, enemy_dir, 'x');
	angle[1] = vec3_ang_axis(plr->move_dir, enemy_dir, 'y');
	angle[2] = vec3_ang_axis(plr->move_dir, enemy_dir, 'z');
	x = rotation_matrix_x(angle[0]);
	y = rotation_matrix_y(angle[1]);
	z = rotation_matrix_z(angle[2]);
	combined = multiply_matrix(&z, &y);
	combined = multiply_matrix(&combined, &x);
	plr->tri[0].p[0] = multi_vec_matrix(&plr->tri[0].p[0], &combined);
	plr->tri[0].p[1] = multi_vec_matrix(&plr->tri[0].p[1], &combined);
	plr->tri[0].p[2] = multi_vec_matrix(&plr->tri[0].p[2], &combined);
	plr->tri[1].p[0] = multi_vec_matrix(&plr->tri[1].p[0], &combined);
	plr->tri[1].p[1] = multi_vec_matrix(&plr->tri[1].p[1], &combined);
	plr->tri[1].p[2] = multi_vec_matrix(&plr->tri[1].p[2], &combined);
	plr->tri[0].normal = vec3_mul(enemy_dir, -1.0f);
	plr->tri[1].normal = vec3_mul(enemy_dir, -1.0f);
}


static t_bool	shoot_player(t_home *home, t_entity *entity, t_player *plr,
		Uint32 t)
{
	t_ray	ray;

	(void)t;
	initialize_player_triangles(plr,
		vec3_unit_vector(vec3_dec(entity->pos, plr->pos)));
	ray.side = ENEMY;
	ray.plr_pos = plr->pos;
	ray.plr_dir = plr->move_dir;
	ray.pos = entity->pos;
	ray.dir = entity->dir;
	ray.start_sector = entity->sector_idx;
	ray.end_sector = plr->cur_sector;
	shooting_handle(home, plr, &ray);
	return (true);
}
		// vec3_ray_triangle_intersect(&tri[0], entity->pos,
		// 	vec3_unit_vector(vec3_dec(plr->pos, entity->pos)))
		// || vec3_ray_triangle_intersect(&tri[1], entity->pos,
		// 	vec3_unit_vector(vec3_dec(plr->pos, entity->pos)))

		// ray.pos = entity->pos;
		// ray.dir = entity->dir;
		// shooting_handle(home, &ray);

/*
**	If attack intersects with a wall.
*/
t_bool	attack_player(t_home *home, t_entity *entity, t_player *plr,
		Uint32 t)
{
	(void)home;
	if (!entity->is_aggroed)
		return (false);
	if (entity->entity_type == skull_skulker)
	{
		if (get_distance_squared(plr->pos, entity->pos) < 2.25f)
		{
			entity->sprite_state = attack;
			if (entity->anim_offset >= 4
				&& (int)(entity->cooldown - t) < 0)
				plr->power_points--;
			pick_next_frame(entity, t);
			return (false);
		}
	}
	if (entity->entity_type == thing)
	{
		entity->sprite_state = attack;
		if (entity->anim_offset >= 4
				&& (int)(entity->cooldown - t) < 0)
			shoot_player(home, entity, plr, t);
		pick_next_frame(entity, t);
		return (true);
	}
	return (false);
}
