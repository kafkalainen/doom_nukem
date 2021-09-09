/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_projectiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:31:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/09 11:37:49 by jnivala          ###   ########.fr       */
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
** 	Uint32		type;
** 	int			sprite_index;
** 	int			entity_index;
** 	int			sprite_state;
** 	int			sector_idx;
** }				t_projectile;
*/

void	initialize_projectile_triangles(t_projectile *projectile)
{
	t_xy	size;

	size = vec2(0.25f, 0.25f);
	projectile->top.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	projectile->top.p[1] = (t_xyz){-0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->top.p[2] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[0] = (t_xyz){-0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[1] = (t_xyz){0.5f * size.x, 0.5f * size.y, 0.0f, 1.0f};
	projectile->bot.p[2] = (t_xyz){0.5f * size.x, -0.5f * size.y, 0.0f, 1.0f};
	if (projectile->is_active)
	{
		projectile->top.type = projectile->sprite_index;
		projectile->bot.type = projectile->sprite_index;
	}
	else
	{
		projectile->top.type = projectile->alt_sprite_index;
		projectile->bot.type = projectile->alt_sprite_index;
	}
	projectile->top.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	projectile->bot.normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
}

static void	initialize_projectile(t_projectile *projectile)
{
	projectile->pos = (t_xyz){0.0f, 0.0f, 0.0f, 1.0f};
	projectile->normal = (t_xyz){0.0f, 0.0f, -1.0f, 0.0f};
	projectile->move_dir = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	projectile->velocity = 0.005f;
	projectile->sprite_index = -bullet;
	projectile->alt_sprite_index = -bullet_decal;
	projectile->is_active = 0;
	initialize_projectile_triangles(projectile);
	initialize_top_texels(&projectile->top);
	initialize_bottom_texels(&projectile->bot);
	projectile->sector_idx = 0;
}

void	assign_projectiles(t_home *home)
{
	Uint32	i;

	home->projectile_pool = (t_projectile **)malloc(sizeof(t_projectile *)
			* MAX_PROJECTILES);
	if (!home->projectile_pool)
		error_output("ERROR: Couldn't allocate memory for projectile pool");
	i = 0;
	home->nbr_of_projectiles = 0;
	home->projectile_idx = -1;
	while (i < MAX_PROJECTILES)
	{
		home->projectile_pool[i] = (t_projectile *)malloc(sizeof(t_projectile));
		if (!home->projectile_pool[i])
			error_output("ERROR: Couldn't allocate memory for a projectile");
		initialize_projectile(home->projectile_pool[i]);
		i++;
	}
}
