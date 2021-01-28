SRCS =	main.c \
		srcs/vec_math/vec2_a.c \
		srcs/vec_math/vec2_b.c \
		srcs/update_player/key_input.c \
		srcs/update_player/mouse_handle.c \
		srcs/update_player/movement.c \
		srcs/update_player/update_player.c \
		srcs/update_screen/draw_floor.c \
		srcs/update_screen/draw_shapes.c \
		srcs/update_screen/put_pixel.c \
		srcs/update_screen/update_screen.c \
		srcs/update_screen/draw_tex_pixel.c \
		srcs/update_screen/steplen.c \
		srcs/update_screen/draw_2d.c \
		srcs/update_screen/update_sector.c \
		srcs/utilities/error_output.c \
		srcs/utilities/setup.c \
		srcs/utilities/audio.c \
		srcs/libft/ft_itoa.c \
		srcs/libft/ft_atoi.c \
		srcs/libft/ft_strings1.c \
		srcs/libft/memory.c \
		srcs/libft/ft_get_next_line.c \
		srcs/libft/ft_putendl_fd.c \
		srcs/raycaster/raycaster.c \
		srcs/parsing/read_map.c

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
LINUX_LIBRARY_PATHS = -L/lib/ -L/usr/local/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
WIN_COMPILER_FLAGS = -w
#LINUX_COMPILER_FLAGS = -Wall -Wextra -Werror
LINUX_COMPILER_FLAGS = -Wall -Wextra
# -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
WIN_LINK_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
LINUX_LINK_FLAGS = -lSDL2 -lSDL2main -lSDL2_mixer -lm -g

.PHONY: all clean fclean re

win:
	gcc $(SRCS) -o play $(WIN_INCLUDE_PATHS) $(WIN_LIBRARY_PATHS) $(WIN_COMPILER_FLAGS) $(WIN_LINK_FLAGS)

linux:
	gcc $(SRCS) -o play $(LINUX_INCLUDE_PATHS) $(LINUX_LIBRARY_PATHS) $(LINUX_COMPILER_FLAGS) $(LINUX_LINK_FLAGS)

all:
	gcc $(SRCS) -o play -I include -L lib -l SDL2-2.0.0
