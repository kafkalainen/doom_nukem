# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 14:21:37 by jnivala           #+#    #+#              #
#    Updated: 2021/06/26 20:19:04 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRCS = \
	main.c \
	editor$(SLASH)setup_editor.c \
	editor$(SLASH)allocate_buttons.c \
	editor$(SLASH)editor_events.c \
	entity_logic$(SLASH)entity.c \
	parsing$(SLASH)calc_average_unit_normals.c \
	parsing$(SLASH)calc_extra_walls.c \
	parsing$(SLASH)calc_wall_and_floor_properties.c \
	parsing$(SLASH)change_door_to_portal.c \
	parsing$(SLASH)check_portal_height_diff.c \
	parsing$(SLASH)check_if_same_point.c \
	parsing$(SLASH)free_sector.c \
	parsing$(SLASH)map_texel.c \
	parsing$(SLASH)parse_number_data.c \
	parsing$(SLASH)parse_sector.c \
	parsing$(SLASH)parse_sector_2.c \
	parsing$(SLASH)parse_surfaces.c \
	parsing$(SLASH)retrieve_adjacent_triangles.c \
	parsing$(SLASH)triangulate_floor_and_ceiling.c \
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
	porting$(SLASH)porting_utils.c \
	raycaster$(SLASH)calc_sector_bounds.c \
	raycaster$(SLASH)colour_scale.c \
	raycaster$(SLASH)get_floor.c \
	raycaster$(SLASH)get_next_wall_tex.c \
	raycaster$(SLASH)get_portal_by_idx.c \
	raycaster$(SLASH)get_wall_height.c \
	raycaster$(SLASH)get_wall_points.c \
	raycaster$(SLASH)line_line_intersection.c \
	raycaster$(SLASH)line_segment_check.c \
	raycaster$(SLASH)recursion_checks.c \
	raycaster$(SLASH)scan_fov.c \
	raycaster$(SLASH)setup_frame.c \
	update_player$(SLASH)check_distances.c \
	update_player$(SLASH)gravity.c \
	update_player$(SLASH)handle_doors.c \
	update_player$(SLASH)key_input.c \
	update_player$(SLASH)mouse_handle.c \
	update_player$(SLASH)check_y_diff.c \
	update_player$(SLASH)player_move.c \
	update_player$(SLASH)player_use.c \
	update_player$(SLASH)special_movement.c \
	update_player$(SLASH)update_player.c \
	update_screen$(SLASH)apply_matrices_a.c \
	update_screen$(SLASH)apply_matrices_b.c \
	update_screen$(SLASH)clip_to_plane.c \
	update_screen$(SLASH)clip_to_viewport_edges.c \
	update_screen$(SLASH)draw_frame.c \
	update_screen$(SLASH)draw_segment.c \
	update_screen$(SLASH)draw_horizontal_line.c \
	update_screen$(SLASH)draw_sector.c \
	update_screen$(SLASH)draw_shapes.c \
	update_screen$(SLASH)draw_shapes2.c \
	update_screen$(SLASH)draw_tex_pixel.c \
	update_screen$(SLASH)draw_tex_triangle.c \
	update_screen$(SLASH)draw_wireframe.c \
	update_screen$(SLASH)init_matrices_a.c \
	update_screen$(SLASH)init_matrices_b.c \
	update_screen$(SLASH)put_pixel.c \
	update_screen$(SLASH)matrix_2d.c \
	update_screen$(SLASH)matrix_3d.c \
	update_screen$(SLASH)update_screen.c \
	update_screen$(SLASH)set_lighting.c \
	utilities$(SLASH)audio.c \
	utilities$(SLASH)error_output.c \
	utilities$(SLASH)fps_timer.c \
	utilities$(SLASH)init_input.c \
	utilities$(SLASH)is_negative.c \
	utilities$(SLASH)mem_functions.c \
	utilities$(SLASH)mem_functions_2.c \
	utilities$(SLASH)pxl_alphabet.c \
	utilities$(SLASH)pxl_numbers.c \
	utilities$(SLASH)raster_queue.c \
	utilities$(SLASH)setup.c \
	utilities$(SLASH)str_pxl.c \
	utilities$(SLASH)system_calls.c \
	utilities$(SLASH)swap_and_sort.c \
	utilities$(SLASH)init_skybox.c \
	vec_math$(SLASH)vec2_a.c \
	vec_math$(SLASH)vec2_b.c \
	vec_math$(SLASH)vec2_c.c \
	vec_math$(SLASH)vec2_d.c \
	vec_math$(SLASH)vec3_a.c \
	vec_math$(SLASH)vec3_b.c \
	vec_math$(SLASH)vec3_c.c \
	vec_math$(SLASH)vec3_d.c \
	vec_math$(SLASH)vec3_e.c \
	vec_math$(SLASH)vec3_f.c \
	menu_systems$(SLASH)launch_modules.c \
	menu_systems$(SLASH)menu_inputs.c \
	menu_systems$(SLASH)menu_setups.c \
	menu_systems$(SLASH)menu_utils.c \
	menu_systems$(SLASH)menu_utils2.c \

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
	headers$(SLASH)editor.h \
	headers$(SLASH)macros.h \
	headers$(SLASH)map.h \
	headers$(SLASH)parser_structs.h \
	headers$(SLASH)parsing.h \
	headers$(SLASH)player.h \
	headers$(SLASH)png_parser.h \
	headers$(SLASH)porting.h \
	headers$(SLASH)program.h \
	headers$(SLASH)raycast.h \
	headers$(SLASH)sector.h \
	headers$(SLASH)syscalls_windows.h \
	headers$(SLASH)vectors.h \
	headers$(SLASH)menu_systems.h

WIN_INCLUDE_PATHS = \
	-ISDL2-2.0.14\i686-w64-mingw32\include\SDL2 \
	-ISDL2_mixer-2.0.4\i686-w64-mingw32\include\SDL2 \
	-Ilibft
LINUX_INCLUDE_PATHS = -I$(SDL_INC) -I$(SDL_MIXER_INC) -Ilibft/

WIN_LIBRARY_PATHS = \
	-LSDL2-2.0.14\i686-w64-mingw32\lib \
	-LSDL2_mixer-2.0.4\i686-w64-mingw32\lib \
	-Llibft
LINUX_LINK_FLAGS = -lSDL2 -lSDL2_mixer -lft -lpthread -lm

CC = gcc
WIN_CFLAGS = -Wall -Wextra -Werror -O3 -g
WIN_LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer-lft -lpthread -lm

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
	SDL_NEW = SDL2-2.0.14\i686-w64-mingw32
	SDL_MIXER_NEW = SDL2_mixer-2.0.4\i686-w64-mingw32
	SLASH = \\
	MKDIR = mkdir
	RM = del /s/q
	RESET := [0m
	RED := [31m
	GREEN := [32m
	YELLOW := [33m
	BLUE := [34m
	MAGENTA := [35m
	CYAN := [36m
	WHITE := [37m
else
	ABS_DIR = $(shell pwd)
	INCLUDES = $(LINUX_INCLUDE_PATHS)
	LIBS = $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --libs) -L$(SDL_MIXER_NEW)lib -Llibft/
	CFLAGS = -Wall -Wextra -Werror -ggdb3 -g $(shell $(ABS_DIR)/SDL2/bin/sdl2-config --cflags)
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
	SDL_ORIG = $(ABS_DIR)/SDL2-2.0.14/
	SDL_NEW = $(ABS_DIR)/SDL2/
	SDL_INC = SDL2/include/SDL2/
	SDL_MIXER_ORIG = $(ABS_DIR)/SDL2_mixer-2.0.4/
	SDL_MIXER_NEW = $(ABS_DIR)/SDL2_mixer/
	SDL_MIXER_INC = SDL2_mixer/include/SDL2/
	CORES = $(shell echo 2+$(shell cat /proc/cpuinfo | grep processor | wc -l) | bc)
endif

S = srcs
O = objs
LIBFT = libft$(SLASH)libft.a
SRC = $(addprefix $S$(SLASH), $(SRCS))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(SDL_NEW):
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
	@IF NOT EXIST $(SDL_NEW) ( install.bat )\
	ELSE ECHO $(GREEN)"Folder exists."$(RESET)
endif

$(SDL_MIXER_NEW):
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
	@IF NOT EXIST $(SDL_MIXER_NEW) ( install_mixer.bat )\
	ELSE ECHO $(GREEN)"Folder exists."$(RESET)
endif

$O:
	$(MKDIR) $@
	$(MKDIR) $@$(SLASH)editor
	$(MKDIR) $@$(SLASH)entity_logic
	$(MKDIR) $@$(SLASH)utilities
	$(MKDIR) $@$(SLASH)update_player
	$(MKDIR) $@$(SLASH)update_screen
	$(MKDIR) $@$(SLASH)parsing
	$(MKDIR) $@$(SLASH)png_parser
	$(MKDIR) $@$(SLASH)porting
	$(MKDIR) $@$(SLASH)raycaster
	$(MKDIR) $@$(SLASH)vec_math
	$(MKDIR) $@$(SLASH)menu_systems

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(SDL_NEW) $(SDL_MIXER_NEW) $(OBJ)
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
	@IF EXIST "SDL2_mixer-devel-2.0.4-mingw.tar.gz" ( $(RM) "SDL2_mixer-devel-2.0.4-mingw.tar.gz" )
	@IF EXIST "SDL2-devel-2.0.14-mingw.tar.gz" ( $(RM) "SDL2-devel-2.0.14-mingw.tar.gz" )
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
