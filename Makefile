# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 14:21:37 by jnivala           #+#    #+#              #
#    Updated: 2021/04/21 11:51:45 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRCS = \
	main.c \
	vec_math$(SLASH)vec2_a.c \
	vec_math$(SLASH)vec2_b.c \
	vec_math$(SLASH)vec2_c.c \
	update_player$(SLASH)key_input.c \
	update_player$(SLASH)mouse_handle.c \
	update_player$(SLASH)movement.c \
	update_player$(SLASH)update_player.c \
	update_player$(SLASH)player_move.c \
	update_screen$(SLASH)draw_shapes.c \
	update_screen$(SLASH)put_pixel.c \
	update_screen$(SLASH)update_screen.c \
	update_screen$(SLASH)draw_tex_pixel.c \
	update_screen$(SLASH)steplen.c \
	update_screen$(SLASH)draw_2d.c \
	update_screen$(SLASH)transform_matrix_2d.c \
	utilities$(SLASH)error_output.c \
	utilities$(SLASH)setup.c \
	utilities$(SLASH)audio.c \
	utilities$(SLASH)linkedlist.c \
	utilities$(SLASH)pxl_alphabet.c \
	utilities$(SLASH)pxl_numbers.c \
	utilities$(SLASH)str_pxl.c \
	raycaster$(SLASH)calc_distances.c \
	raycaster$(SLASH)calc_ground_texels.c \
	raycaster$(SLASH)calc_sector_texels.c \
	raycaster$(SLASH)calc_wall_texels.c \
	raycaster$(SLASH)draw_segment.c \
	raycaster$(SLASH)get_distance.c \
	raycaster$(SLASH)get_wall_points.c \
	raycaster$(SLASH)line_line_intersection.c \
	raycaster$(SLASH)line_segment_check.c \
	raycaster$(SLASH)perspective_offset.c \
	raycaster$(SLASH)recursion_checks.c \
	raycaster$(SLASH)scan_fov.c \
	raycaster$(SLASH)setup_frame.c \
	parsing$(SLASH)calc_norm_vectors.c \
	parsing$(SLASH)free_sector.c \
	parsing$(SLASH)parse_number_data.c \
	parsing$(SLASH)parse_sector.c \
	png_parser$(SLASH)color_utils.c \
	png_parser$(SLASH)crc.c \
	png_parser$(SLASH)filters.c \
	png_parser$(SLASH)header.c \
	png_parser$(SLASH)inflate_setups.c \
	png_parser$(SLASH)inflate_trees.c \
	png_parser$(SLASH)inflate_utils.c \
	png_parser$(SLASH)inflate_utils2.c \
	png_parser$(SLASH)inflate.c \
	png_parser$(SLASH)parser.c \
	png_parser$(SLASH)texture.c \
	png_parser$(SLASH)unfilter.c \
	png_parser$(SLASH)parser_utils.c \
	png_parser$(SLASH)parser_utils2.c \
	porting$(SLASH)png.c \
	porting$(SLASH)create_mapfile.c \
	porting$(SLASH)open_file1.c \
	porting$(SLASH)open_file2.c \
	porting$(SLASH)validate_sectors_data.c \
	porting$(SLASH)validate_sectors_data_2.c \

HEADERS = \
	libft$(SLASH)libft.h \
	headers$(SLASH)doom_nukem.h \
	headers$(SLASH)audio.h \
	headers$(SLASH)calculations.h \
	headers$(SLASH)caster.h \
	headers$(SLASH)colours.h \
	headers$(SLASH)drawing_functions.h \
	headers$(SLASH)entity.h \
	headers$(SLASH)events.h \
	headers$(SLASH)macros.h \
	headers$(SLASH)map.h \
	headers$(SLASH)parser_structs.h \
	headers$(SLASH)parsing.h \
	headers$(SLASH)player_functions.h \
	headers$(SLASH)player.h \
	headers$(SLASH)png_parser.h \
	headers$(SLASH)porting.h \
	headers$(SLASH)program.h \
	headers$(SLASH)raycast.h \
	headers$(SLASH)sector.h \
	headers$(SLASH)vectors.h \

ABS_DIR = $(shell pwd)
SDL_ORIG = $(ABS_DIR)/SDL2-2.0.14/
SDL_NEW = $(ABS_DIR)/SDL2/
SDL_INC = SDL2/include/SDL2/
SDL_MIXER_ORIG = $(ABS_DIR)/SDL2_mixer-2.0.4/
SDL_MIXER_NEW = $(ABS_DIR)/SDL2_mixer/
SDL_MIXER_INC = SDL2_mixer/include/SDL2/

WIN_INCLUDE_PATHS = \
	-ISDL2-2.0.14\i686-w64-mingw32\include\SDL2 \
	-ISDL2_mixer-2.0.4\i686-w64-mingw32\include\SDL2 \
	-Ilibft
LINUX_INCLUDE_PATHS = -I$(SDL_INC) -I$(SDL_MIXER_INC) -Ilibft/

WIN_LIBRARY_PATHS = \
	-LSDL2-2.0.14\i686-w64-mingw32\lib \
	-LSDL2_mixer-2.0.4\i686-w64-mingw32\lib \
	-Llibft
LINUX_LIBRARY_PATHS = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs) -L$(SDL_MIXER_NEW)lib -Llibft/
LINUX_LINK_FLAGS = -lSDL2 -lSDL2_mixer -lft -lm -g

CC = gcc
WIN_CFLAGS = -Wall -Wextra -Werror -O3
LINUX_CFLAGS = -Wall -Wextra  -O3 -g
LINUX_CFLAGS += $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)

WIN_LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lft -lm

CORES = $(shell echo 2+$(shell cat /proc/cpuinfo | grep processor | wc -l) | bc)

#mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
#mkfile_dir := $(dir $(mkfile_path))

ifeq ($(OS),Windows_NT)
	TARGET_SYSTEM := Windows
else
	TARGET_SYSTEM := $(shell uname -s)
	TARGET_SYSTEM := $(patsubst CYGWIN%,Cygwin,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MSYS%,MSYS,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MINGW%,MSYS,$(TARGET_SYSTEM))
endif

ifeq ($(TARGET_SYSTEM),Windows)
	NAME = doom-nukem.exe
	INCLUDES = $(WIN_INCLUDE_PATHS)
	LIBS = $(WIN_LIBRARY_PATHS)
	CFLAGS = $(WIN_CFLAGS)
	LDFLAGS = $(WIN_LFLAGS)
	SDL2_BUILD := .\SDL2-2.0.14\i686-w64-mingw32
	SLASH = \\
	MKDIR = mkdir
	RM = del $(SLASH)s/q
	RESET :=
	RED :=
	GREEN :=
	YELLOW :=
	BLUE :=
	MAGENTA :=
	CYAN :=
	WHITE :=
else
	INCLUDES = $(LINUX_INCLUDE_PATHS)
	LIBS = $(LINUX_LIBRARY_PATHS)
	CFLAGS = $(LINUX_CFLAGS)
	LDFLAGS = $(LINUX_LINK_FLAGS)
	SLASH = /
	MKDIR := mkdir -p
	RM = /bin/rm -rf
	RESET = "\033[0m"
	RED = "\033[0;31m"
	GREEN = "\033[0;32m"
	YELLOW = "\033[0;33m"
	BLUE = "\033[0;34m"
	MAGENTA = "\033[0;35m"
	CYAN = "\033[0;36m"
	WHITE = "\033[0;37m"
endif

S = srcs
O = objs
LIBFT = libft$(SLASH)libft.a
SRC = $(addprefix $S$(SLASH), $(SRCS))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all clean fclean re sdl sdl-mixer

all: $(NAME)

echo:
	echo INCLUDES: $(INCLUDES)
	echo LIBS:  $(LIBS)
	echo CFLAGS: $(CFLAGS)
	echo LDFLAGS: $(LDFLAGS)

sdl:
ifeq ($(TARGET_SYSTEM), Linux)
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2-2.0.14.tar.gz" ]; then \
	wget https://www.libsdl.org/release/SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_ORIG)" ]; then \
	tar -xzf SDL2-2.0.14.tar.gz; \
	fi
	@if [ ! -d "$(SDL_NEW)" ] ; then \
	mkdir -p $(SDL_NEW); \
	cd $(SDL_NEW) && \
	$(SDL_ORIG)./configure --prefix=$(SDL_NEW) && \
	make -j$(CORES) && make install ; \
	else    \
	make -j$(CORES) -C $(SDL_NEW) ; \
	fi
else
	@IF NOT EXIST "SDL2-2.0.14\x86_64-w64-mingw32" ( install.bat )\
	ELSE ECHO $(GREEN)"Folder exists."$(RESET)
endif

sdl-mixer:
ifeq ($(TARGET_SYSTEM), Linux)
	@if [ ! $(shell command -v wget 2> /dev/null) ]; then \
	sudo apt-get install wget -y; \
	fi
	@if [ ! -f "SDL2_mixer-2.0.4.tar.gz" ]; then \
	wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_ORIG)" ]; then \
	tar -xzf SDL2_mixer-2.0.4.tar.gz; \
	fi
	@if [ ! -d "$(SDL_MIXER_NEW)" ] ; then \
	mkdir -p $(SDL_MIXER_NEW); \
	cd $(SDL_MIXER_NEW) && \
	$(SDL_MIXER_ORIG)./configure --prefix $(SDL_MIXER_NEW) && \
	make -j$(CORES) && make install; \
	else \
	make -j$(CORES) -C $(SDL_MIXER_NEW) ; \
	fi
else
	@IF NOT EXIST "SDL2-2.0.14\x86_64-w64-mingw32" ( install.bat )\
	ELSE ECHO $(GREEN)"Folder exists."$(RESET)
endif

$O:
	$(MKDIR) $@
	$(MKDIR) $@$(SLASH)utilities
	$(MKDIR) $@$(SLASH)update_player
	$(MKDIR) $@$(SLASH)update_screen
	$(MKDIR) $@$(SLASH)parsing
	$(MKDIR) $@$(SLASH)png_parser
	$(MKDIR) $@$(SLASH)porting
	$(MKDIR) $@$(SLASH)raycaster
	$(MKDIR) $@$(SLASH)vec_math

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) sdl sdl-mixer $(OBJ)
	$(CC) -o $@ $(INCLUDES) $(LIBS) $(CFLAGS) $(OBJ) $(LDFLAGS)
	@echo $(GREEN)Compiled executable $(NAME).
	@echo Run the map files $(NAME) map_files/map.TEST.
	@echo Running tests.sh tests executable with invalid maps.$(RESET)

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	@$(RM) $(wildcard $(OBJ))
endif

cleanobjdir: cleanobj
ifeq ($(TARGET_SYSTEM), Linux)
	@$(RM) $O
else
	@IF EXIST $O ( rd /s /q "$O" )
endif

clean: cleanobjdir
ifeq ($(TARGET_SYSTEM), Linux)
	@if [ -d "$(SDL_NEW)" ] ; then \
	make -C $(SDL_NEW) clean ; \
	fi;
	@if [ -d "$(SDL_MIXER_NEW)" ] ; then \
	make -C $(SDL_MIXER_NEW) clean ; \
	fi;
endif
	@make -C libft clean
	@echo $(GREEN)Cleaned projects from object files.$(RESET)

fclean: clean
ifeq ($(TARGET_SYSTEM), Windows)
	@IF EXIST SDL2-2.0.14 ( $(RM) "SDL2-2.0.14" )
	@IF EXIST SDL2-2.0.14 ( rd /s /q "SDL2-2.0.14" )
	@IF EXIST SDL2_mixer-2.0.4 ( $(RM) "SDL2_mixer-2.0.4" )
	@IF EXIST SDL2_mixer-2.0.4 ( rd /s /q "SDL2_mixer-2.0.4" )
	@IF EXIST $(NAME) ( $(RM) "$(NAME)") \
	ELSE ( ECHO $(CYAN)No binary to remove. $(RESET) )
else
	@$(RM) $(NAME)
	@$(RM) $(SDL_NEW)
	@$(RM) $(SDL_MIXER_NEW)
	@$(RM) $(SDL_ORIG)
	@$(RM) $(SDL_MIXER_ORIG)
	@$(RM) SDL2_mixer-2.0.4.tar.gz
	@$(RM) SDL2-2.0.14.tar.gz
endif
	@make -C libft fclean
	@echo $(GREEN)Removed binaries and libraries.$(RESET)

re: fclean all
