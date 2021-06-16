/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:16:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/16 17:05:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	init_input_values(t_input *input)
{
	input->down = 0;
	input->up = 0;
	input->right = 0;
	input->left = 0;
	input->rot_right = 0;
	input->rot_left = 0;
	input->wireframe = 0;
	input->minimap = 1;
	input->info = 1;
	input->mouse = 1;
	input->debug_up = 0;
	input->debug_down = 0;
	input->debug_right = 0;
	input->debug_left = 0;
	input->jetpack = 0;
	input->jump = 0;
	input->crouch = 0;
	input->use = 0;
}
