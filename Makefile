SRCS =	main.c \
		srcs/vec_math/vec2_a.c \
		srcs/vec_math/vec2_b.c \
		srcs/update_player/key_input.c \
		srcs/update_player/mouse_handle.c \
		srcs/update_player/movement.c \
		srcs/update_player/update_player.c \
		srcs/update_screen/draw_fov.c \
		srcs/update_screen/draw_minimap.c \
		srcs/update_screen/draw_wall.c \
		srcs/update_screen/put_pixel.c \
		srcs/update_screen/update_screen.c \
		srcs/utilities/error_output.c \
		srcs/utilities/setup.c \
		srcs/libft/ft_itoa.c \
		srcs/libft/ft_strings1.c \
		srcs/libft/memory.c \
		srcs/libft/ft_get_next_line.c

#INCLUDE_PATHS specifies the additional include paths we'll need
WIN_INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
WIN_LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
WIN_COMPILER_FLAGS = -w
# -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
WIN_LINK_FLAGS = -lmingw32 -lSDL2main -lSDL2

win:
	gcc $(SRCS) -o play $(WIN_INCLUDE_PATHS) $(WIN_LIBRARY_PATHS) $(WIN_COMPILER_FLAGS) $(WIN_LINK_FLAGS)

all: 
	gcc $(SRCS) -o play -I include -L lib -l SDL2-2.0.0
