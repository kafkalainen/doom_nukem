/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_projectiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:31:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/08/19 11:09:21 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"


/*
** 	typedef	struct	s_projectile
**	{
** 	t_xyz		pos;
** 	t_xyz		normal;
** 	t_xyz		move_dir;
** 	float		velocity;
** 	t_triangle	top;
** 	t_triangle	bot;
** 	Uint32		is_active;
** 	Uint32		entity_type;
** 	int			sprite_index;
** 	int			entity_index;
** 	int			sprite_state;
** 	int			sector_idx;
** }				t_projectile;
*/

static void	initialize_projectile_triangles(t_projectile *projectile)
{
	t_xy	size;

	size = (t_xy){0.25f, 0.25f};
	projectile->top.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	projectile->top.p[1] = (t_xyz){-0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->top.p[2] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[1] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[2] = (t_xyz){0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
}

static void	initialize_projectile(t_projectile *projectile)
{
	projectile->pos = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	projectile->normal = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	projectile->move_dir = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	projectile->velocity = 0.005f;
	projectile->velocity = 0.005f;
	initialize_projectile_triangles(projectile);
	initialize_top_texels(&projectile->top);
	initialize_bottom_texels(&projectile->bot);
	projectile->is_active = 0;
	projectile->sector_idx = 0;
	projectile->sprite_index = bullet_decal;
}

void	assign_projectiles(t_home *home)
{
	Uint32	i;
	home->projectile_pool = (t_projectile**)malloc(sizeof(t_projectile*)
		* 100);
	if (!home->projectile_pool)
		error_output("ERROR: Couldn't allocate memory for projectile pool");
	i = 0;
	home->nbr_of_projectiles = 0;
	while (i < 100)
	{
		home->projectile_pool[i] = (t_projectile*)malloc(sizeof(t_projectile));
		if (!home->projectile_pool[i])
			error_output("ERROR: Couldn't allocate memory for a projectile");
		initialize_projectile(home->projectile_pool[i]);
		i++;
	}
}
