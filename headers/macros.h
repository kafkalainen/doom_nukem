/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:17 by tmaarela          #+#    #+#             */
/*   Updated: 2021/02/25 09:47:54 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFF_SIZE 16
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define WALL_HEIGHT 0.5f
# define TEX_SIZE 128
# define FOV 1.57079616f
# define MAP_MAX_LINES 128
# define MINIMAP_SIZE 10

# define NUM_TEX 8

# define PLR_DIR 0.785398163f

# define MAX_INT (2147483647)
# define MIN_INT (-MAX_INT - 1)
# define MAX_UINT ((unsigned int)-1)
# define MAX_ULONG ((unsigned long)-1)
# define MAX_ULLONG ((unsigned long long)-1)

# define PI (3.1415926535f)
# define PI_BY_TWO (1.570796326f)
# define TWO_PI (6.283185307f)
# define RAD_TO_DEG (57.29577951f)
# define DEG_TO_RAD (0.0174532925f)
# define SQR2 (0.7071067812)

# define TRUE (1)
# define FALSE (0)
# define AND (&&)
# define OR (||)

# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
**
*** Keyboard and Mouse macros
**
*/

# define k_esc SDLK_ESCAPE
# define k_space SDLK_SPACE
# define k_ctrl SDLK_LCTRL
# define k_shift SDLK_LSHIFT

# define k_up SDLK_UP
# define k_down SDLK_DOWN
# define k_left SDLK_LEFT
# define k_right SDLK_RIGHT

# define k_w SDLK_w
# define k_s SDLK_s
# define k_a SDLK_a
# define k_d SDLK_d
# define k_q SDLK_q
# define k_e SDLK_e
# define k_z SDLK_z
# define k_x SDLK_x

#endif
