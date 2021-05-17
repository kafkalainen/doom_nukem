/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ground_texels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:54:25 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/17 10:54:34 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static float	vec2_dist_from_point(t_xy *x1, t_xy *x2, t_xy *x0)
{
	return (fabsf(((x2->x - x1->x) * (x1->y - x0->y)
		- (x1->x - x0->x) * (x2->y - x1->y)))
		/ vec2_eucl_dist(*x1, *x2));
}

static float	clip_to_0_1_range(float nb)
{
	if (nb < 0.0f)
		return (0.0f);
	else if (nb > 1.0f)
		return (1.0f);
	else
		return (nb);
}

static void	clip_offsets_to_range(t_plgn *ground_uv)
{
	ground_uv->top_left.x = clip_to_0_1_range(ground_uv->top_left.x);
	ground_uv->top_left.y = clip_to_0_1_range(ground_uv->top_left.y);
	ground_uv->top_right.x = clip_to_0_1_range(ground_uv->top_right.x);
	ground_uv->top_right.y = clip_to_0_1_range(ground_uv->top_right.y);
	ground_uv->bottom_left.x = clip_to_0_1_range(ground_uv->bottom_left.x);
	ground_uv->bottom_left.y = clip_to_0_1_range(ground_uv->bottom_left.y);
	ground_uv->bottom_right.x = clip_to_0_1_range(ground_uv->bottom_right.x);
	ground_uv->bottom_right.y = clip_to_0_1_range(ground_uv->bottom_right.y);
}

static void	calc_offsets(t_sector *sector, t_frame *frame, t_player *plr)
{
	plr = plr;
	frame->ground_uv.top_left.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.l_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_left.z = vec3_eucl_dist(frame->outer_box.bottom_left);
	frame->ground_uv.top_right.x = vec2_dist_from_point(&sector->floor_top_right,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_top_right, sector->floor_top_left);
	frame->ground_uv.top_right.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &frame->left.r_pt)
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.top_right.z = vec3_eucl_dist(frame->outer_box.bottom_right);
	frame->ground_uv.bottom_left.x = frame->ground_uv.top_left.x;
	frame->ground_uv.bottom_left.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &(t_xy){0.0f, 0.0f})
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.bottom_left.z = 10.0f;
	frame->ground_uv.bottom_right.x = frame->ground_uv.top_right.x;
	frame->ground_uv.bottom_right.y = vec2_dist_from_point(&sector->floor_bottom_left,
		&sector->floor_bottom_right, &(t_xy){0.0f, 0.0f})
		/ vec2_eucl_dist(sector->floor_bottom_left, sector->floor_top_left);
	frame->ground_uv.bottom_right.z = 10.0f;
}

static void	calc_inverse_of_z(t_xyz *top_left, t_xyz *top_right,
	t_xyz *bottom_left, t_xyz *bottom_right)
{
	*top_left = inv_z(*top_left);
	*top_right = inv_z(*top_right);
	*bottom_left = inv_z(*bottom_left);
	*bottom_right = inv_z(*bottom_right);
}

/*
**	Amount of ground texels is too high on y axis.
**	1. When interpolated from Outer box.y to SCREEN_HEIGHT,
**	texels "run towards player."
**	2. When interpolated with 1 / Y', no effect. Makes Y so high, that only the first row is printed.
**	3. If z is not incremented in the drawing loop, it causes texture to turn more in to wall like.
**	4. Not working with plr->z, nor adding static variable to the z at the bottom. Texels look somewhat correct,
**	when z is around 10.0f for frame->ground_bottom_right and frame->ground_bottom_left.
**	5. Testing with another idea: Player's gaze is shaped like a pie, instead of an square.
**	Didn't work. No major improvement.
**	6. Trying the z as the actual distance. Did not work. vec2_perp_dist(sector->floor_top_right);
**	7. Tested that are the texels mapped to the correct range, and they really are!
**	8. Testing without inverting the z. Got some of the textures drawn, and realised that there are problems in
**	texture offsetting. If we use linear interpolation of Y' from the bottom of the floor to the bottom of the
**	screen, it will enlarge the texture and squeeze it based on how many rows there are visible. We need to calculate,
**	how much depth is stepped at each step of the rows of Y' towards the player.
**	Also, the texture is not properly streched to the whole span of the floor. When the intersection point is at left wall,
**	it will strech the texture.
**	9. z needs to be lower close to the player's gaze, and larger at the root of the floor.
**	10. What is the actual distance? Z is perpendicular distance, so save that. Also, z of the another is close to zero,
**	so reset to that. What is the actual problem is how the floor is drawn.
**	Width of the x should be significantly smaller when closer to the player,
**	so x can't be the same when closer to the viewer. It should drop proportion to the distance.
**	The real problem is that how much smaller is it exactly.
**	11. Testing with Lodev's tutorial just by mapping texels directly, and not inverting the texture coordinates.
**	Calculating the weight at the draw function itself. Perpentual distance to zero at the end, and perpentual distance
**	to frame->outer_box.bottom_left.z at top_left. Can't say it was a success, but noticed that we cannot add z
**	to the texel, it needs to be subtracted at each y step.
**	12. Start to do the calculations for the entire sector at once. Traverse the points between left and right,
**	and continue.
*/

void	calc_ground_texels(t_sector *sector, t_frame *frame, t_player *plr)
{
	calc_offsets(sector, frame, plr);
	clip_offsets_to_range(&frame->ground_uv);
	calc_inverse_of_z(
		&frame->ground_uv.top_left, &frame->ground_uv.top_right,
		&frame->ground_uv.bottom_left, &frame->ground_uv.bottom_right);
	frame->ground_uv_step.x = interpolate_points(
		frame->ground_uv.top_left.x, frame->ground_uv.top_right.x,
		frame->outer_box.bottom_left.x, frame->outer_box.bottom_right.x);
	frame->ground_uv_step.y = interpolate_points(
		frame->ground_uv.top_left.y, frame->ground_uv.bottom_left.y,
		frame->outer_box.bottom_left.y, SCREEN_HEIGHT);
	frame->ground_uv_step.z = interpolate_points(
		frame->ground_uv.top_left.z, frame->ground_uv.bottom_left.z,
		frame->outer_box.bottom_left.y, SCREEN_HEIGHT);
}
