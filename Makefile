SRCS =	main.c \
		srcs/vec_math/vec2_a.c \
		srcs/vec_math/vec2_b.c \
		srcs/update_player/key_input.c \
		srcs/update_player/mouse_handle.c \
		srcs/update_player/movement.c \
		srcs/update_player/update_player.c \
		srcs/update_screen/draw_shapes.c \
		srcs/update_screen/put_pixel.c \
		srcs/update_screen/update_screen.c \
		srcs/update_screen/draw_tex_pixel.c \
		srcs/update_screen/steplen.c \
		srcs/update_screen/draw_2d.c \
		srcs/update_screen/update_sector.c \
		srcs/update_screen/transform_matrix_2d.c \
		srcs/utilities/error_output.c \
		srcs/utilities/setup.c \
		srcs/utilities/audio.c \
		srcs/utilities/linkedlist.c \
		srcs/libft/ft_itoa.c \
		srcs/libft/ft_ftoa.c \
		srcs/libft/ft_atoi.c \
		srcs/libft/ft_strings1.c \
		srcs/libft/memory.c \
		srcs/libft/ft_get_next_line.c \
		srcs/libft/ft_putendl_fd.c \
		srcs/libft/ft_memcpy.c \
		srcs/libft/ft_memalloc.c \
		srcs/raycaster/line_line_intersection.c \
		srcs/raycaster/scan_fov.c \
		srcs/raycaster/get_left_point.c \
		srcs/raycaster/get_right_point.c \
		srcs/raycaster/setup_frame.c \
		srcs/raycaster/continue_from_next_point.c \
		srcs/raycaster/continue_from_last_sector.c \
		srcs/raycaster/check_connection.c \
		srcs/raycaster/check_if_portal.c \
		srcs/raycaster/check_if_same_point.c \
		srcs/raycaster/check_if_same_wall.c \
		srcs/raycaster/calc_visible_walls.c \
		srcs/raycaster/get_distance.c \
		srcs/raycaster/ceil_to_pixel.c \
		srcs/parsing/read_map.c	\
		srcs/png_parser/color_utils.c \
		srcs/png_parser/crc.c \
		srcs/png_parser/filters.c \
		srcs/png_parser/header.c \
		srcs/png_parser/inflate_setups.c \
		srcs/png_parser/inflate_trees.c \
		srcs/png_parser/inflate_utils.c \
		srcs/png_parser/inflate_utils2.c \
		srcs/png_parser/inflate.c \
		srcs/png_parser/parser.c \
		srcs/png_parser/texture.c \
		srcs/png_parser/unfilter.c \
		srcs/png_parser/utils.c \
		srcs/porting/png.c \
		srcs/raycaster/ft_draw_wall.c \
		srcs/libft/ft_putnbr.c \
		srcs/libft/ft_putchar.c

HEADERS = \
		doom_nukem.h\
		dn_map.h\

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

#INCLUDE_PATHS specifies the additional include paths we'll need
WIN_INCLUDE_PATHS = -ISDL2\include\SDL2 -ISDL2_mixer_win\include\SDL2
LINUX_INCLUDE_PATHS = -I/include/SDL2/

#LIBRARY_PATHS specifies the additional library paths we'll need
WIN_LIBRARY_PATHS = -LSDL2\lib -LSDL2_mixer_win\lib
LINUX_LIBRARY_PATHS = -L/lib/ -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu/

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
WIN_COMPILER_FLAGS = -w
#LINUX_COMPILER_FLAGS = -Wall -Wextra -Werror
LINUX_COMPILER_FLAGS = -Wall -Wextra
# -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
WIN_LINK_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
LINUX_LINK_FLAGS = -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf -lm -g

.PHONY: all clean fclean re

win:
	gcc $(SRCS) -o play $(WIN_INCLUDE_PATHS) $(WIN_LIBRARY_PATHS) $(WIN_COMPILER_FLAGS) $(WIN_LINK_FLAGS)

# dependencies:
# 	sudo apt-get install libsdl2-dev libsdl2-mixer-2.0-0 libsdl2-ttf-dev

linux: #dependencies
	gcc $(SRCS) -o play $(LINUX_INCLUDE_PATHS) $(LINUX_LIBRARY_PATHS) $(LINUX_COMPILER_FLAGS) $(LINUX_LINK_FLAGS)

all:
	gcc $(SRCS) -o play -I include -L lib -l SDL2-2.0.0
