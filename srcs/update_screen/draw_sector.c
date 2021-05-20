// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   draw_sector.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/05/17 15:43:24 by jnivala           #+#    #+#             */
// /*   Updated: 2021/05/20 12:22:14 by jnivala          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../headers/doom_nukem.h"

// static void	fit_to_screen_space_x(t_xy *offset, t_xyz *texel,
// 	int *height, float *uv_step_y)
// {
// 	(void)uv_step_y;
// 	(void)texel;
// 	if (offset->x < 0)
// 	{
// 		// texel->y += *uv_step_y * -offset->y;
// 		*height += offset->x;
// 		offset->x = 0;
// 	}
// 	if (*height > SCREEN_WIDTH)
// 		*height = SCREEN_WIDTH;
// }

// static void	draw_horizontal_floor_strip(t_xy offset, int width,
// 							t_texture *tex, t_frame *frame)
// {
// 	int		cur_x;
// 	// t_xyz	corr_texel;
// 	t_xyz	texel;
// 	// Uint32	colour;

// 	cur_x = 0;
// 	(void)tex;
// 	// texel = frame->middle_uv.top_left;
// 	// corr_texel = texel;
// 	fit_to_screen_space_x(&offset, &texel, &width, &frame->ground_uv_step.x);
// 	while (cur_x < width)
// 	{
// 		// corr_texel = inv_z(texel);
// 		// if (cur_y + offset.y >= 0 && cur_y + offset.y < SCREEN_HEIGHT)
// 		// {
// 		// 	colour = colour_scale(get_texel(corr_texel.x * (tex->w - 1),
// 		// 				corr_texel.y * (tex->h - 1), tex),
// 		// 			frame->left.wall->wall_facing);
// 			put_pixel(frame->buffer, cur_x + offset.x, offset.y, blueviolet);
// 		// }
// 		cur_x++;
// 		// texel.y += frame->ground_uv_step.y;
// 	}
// }
