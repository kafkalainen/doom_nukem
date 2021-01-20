/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaarela <tmaarela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:17 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/20 13:45:17 by tmaarela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFF_SIZE 16
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define WALL_HEIGHT 0.5
# define TEX_SIZE 128
# define FOV 90.0
# define MAP_MAX_LINES 128
# define MINIMAP_SIZE 10

# define HORIZONTAL_WALL 1
# define VERTICAL_WALL 0

# define MAX_INT (2147483647)
# define MIN_INT (-MAX_INT - 1)
# define MAX_UINT ((unsigned int)-1)
# define MAX_ULONG ((unsigned long)-1)
# define MAX_ULLONG ((unsigned long long)-1)

# define PI (3.1415926535897932384626433832795f)
# define PI_BY_TWO (1.5707963267948966192313216916398f)
# define TWO_PI (6.283185307179586476925286766559f)
# define RAD_TO_DEG (57.295779513082320876798154814105f)
# define DEG_TO_RAD (0.017453292519943295769236907684886f)

# define TRUE (1)
# define FALSE (0)
# define AND (&&)
# define OR (||)

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

#endif
