/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:17 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/05 10:33:18 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFF_SIZE 16
# define NBR_BUTTONS 14
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define WALL_HEIGHT 0.5f
# define TEX_SIZE 128
# define FOV 1.57079616f
# define MAP_MAX_LINES 128
# define MINIMAP_SIZE 10

# define NUM_TEX 8

# define MAX_INT 2147483647
# define PLR_DIR 0.785398163f
# define INV_PI_BY_TWO 0.1591549367f
# define PI 3.1415926535f
# define PI_BY_TWO 1.570796326f
# define TWO_PI 6.283185307f
# define RAD_TO_DEG 57.29577951f
# define DEG_TO_RAD 0.0174532925f
# define SQR2 0.7071067812f
# define Z_NEAR 0.1f
# define Z_FAR 1000.0f
# define TRUE 1
# define FALSE 0
# define AND &&
# define OR ||
# define EDITOR 4
# define GAME_LOOP 3
# define MAP_MENU 2
# define MAIN_MENU 1
# define QUIT -1
# define MAX_THREADS 2

/*
** Compass directions
*/

# define N 6.28318530718f
# define NW 0.7853981634f
# define W 1.5707963268f
# define SW 2.3561944902f
# define S 3.14159265359f
# define SE 3.926990817f
# define E 4.71238898039f
# define NE 5.49778714378f

#endif
