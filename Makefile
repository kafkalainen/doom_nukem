# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 14:21:37 by jnivala           #+#    #+#              #
#    Updated: 2021/09/16 10:34:57 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRCS = \
	main.c \
	editor$(SLASH)allocate_buttons.c \
	editor$(SLASH)button_actions.c \
	editor$(SLASH)bounding_box_checks.c \
	editor$(SLASH)calculate_centroid.c \
	editor$(SLASH)check_all_sectors_for_intersecting_lines.c \
	editor$(SLASH)check_for_intersecting_lines.c \
	editor$(SLASH)check_grid_events.c \
	editor$(SLASH)check_if_another_sector_is_inside.c \
	editor$(SLASH)create_portals.c \
	editor$(SLASH)check_if_non_convex.c \
	editor$(SLASH)draw_buttons.c \
	editor$(SLASH)draw_visual_help_lines.c \
	editor$(SLASH)draw_editor_entities.c \
	editor$(SLASH)draw_editor_sectors.c \
	editor$(SLASH)draw_editor_sector_bbox.c \
	editor$(SLASH)draw_entity_textfields.c \
	editor$(SLASH)draw_sector_special_info.c \
	editor$(SLASH)draw_sector_textfields.c \
	editor$(SLASH)draw_text_and_strings.c \
	editor$(SLASH)draw_wall_textfields.c \
	editor$(SLASH)draw_grid.c \
	editor$(SLASH)draw_ui.c \
	editor$(SLASH)editor_add_new_sector_to_list_end.c \
	editor$(SLASH)editor_create_entity.c \
	editor$(SLASH)editor_entity_creation_helpers.c \
	editor$(SLASH)editor_events.c \
	editor$(SLASH)editor_entity.c \
	editor$(SLASH)editor_edit_entity.c \
	editor$(SLASH)editor_entity_link_management.c \
	editor$(SLASH)editor_entity_link_booleans.c \
	editor$(SLASH)editor_create_new_sector.c \
	editor$(SLASH)editor_delete_entity.c \
	editor$(SLASH)editor_delete_wall.c \
	editor$(SLASH)editor_load_map.c \
	editor$(SLASH)editor_load_map2.c \
	editor$(SLASH)editor_load_map3.c \
	editor$(SLASH)editor_load_map4.c \
	editor$(SLASH)editor_load_map5.c \
	editor$(SLASH)editor_reset_player_and_end.c \
	editor$(SLASH)editor_save_map.c \
	editor$(SLASH)editor_sort_sector_vertices.c \
	editor$(SLASH)event_actions.c \
	editor$(SLASH)free_editor_data.c \
	editor$(SLASH)get_clicked_entity.c \
	editor$(SLASH)get_clicked_sector.c \
	editor$(SLASH)get_clicked_wall.c \
	editor$(SLASH)get_linked_entity.c \
	editor$(SLASH)get_linked_sector.c \
	editor$(SLASH)get_entity_with_idx.c \
	editor$(SLASH)get_editor_sector_with_idx.c \
	editor$(SLASH)get_ndc.c \
	editor$(SLASH)handle_events.c \
	editor$(SLASH)handle_events2.c \
	editor$(SLASH)handle_events3.c \
	editor$(SLASH)handle_events4.c \
	editor$(SLASH)initialize_actions.c \
	editor$(SLASH)initialize_editor_values.c \
	editor$(SLASH)launch_editor.c \
	editor$(SLASH)ndc_to_world.c \
	editor$(SLASH)notify_user.c \
	editor$(SLASH)rotate_through_entities.c \
	editor$(SLASH)read_input_string.c \
	editor$(SLASH)sector_actions.c \
	editor$(SLASH)translate_towards_centroid.c \
	editor$(SLASH)wall_points.c \
	editor$(SLASH)wall_points2.c \
	editor$(SLASH)world_to_screen.c \
	entity_logic$(SLASH)activate_lift.c \
	entity_logic$(SLASH)attack_player.c \
	entity_logic$(SLASH)check_aggro.c \
	entity_logic$(SLASH)determine_entity_angle.c \
	entity_logic$(SLASH)die.c \
	entity_logic$(SLASH)entity_move.c \
	entity_logic$(SLASH)face_entity_towards_player.c \
	entity_logic$(SLASH)handle_activation.c \
	entity_logic$(SLASH)lock_lift.c \
	entity_logic$(SLASH)other_dir.c \
	entity_logic$(SLASH)turn_on_lights.c \
	entity_logic$(SLASH)update_lifts.c \
	entity_logic$(SLASH)update_entities.c \
	entity_logic$(SLASH)update_projectiles.c \
	entity_logic$(SLASH)take_damage.c \
	parsing$(SLASH)assign_entity_properties.c \
	parsing$(SLASH)assign_projectiles.c \
	parsing$(SLASH)calc_lift_doors.c \
	parsing$(SLASH)calc_extra_walls.c \
	parsing$(SLASH)calc_light_sources.c \
	parsing$(SLASH)calc_map_properties.c \
	parsing$(SLASH)calc_unit_normals.c \
	parsing$(SLASH)change_door_to_portal.c \
	parsing$(SLASH)check_portal_height_diff.c \
	parsing$(SLASH)check_if_same_point.c \
	parsing$(SLASH)free_sector.c \
	parsing$(SLASH)generate_doors.c \
	parsing$(SLASH)get_next_value.c \
	parsing$(SLASH)initialize_entity_textures.c \
	parsing$(SLASH)initialize_entity_triangles.c \
	parsing$(SLASH)map_texel.c \
	parsing$(SLASH)parse_entity_data.c \
	parsing$(SLASH)parse_number_data.c \
	parsing$(SLASH)parse_sector_a.c \
	parsing$(SLASH)parse_sector_b.c \
	parsing$(SLASH)parse_surfaces.c \
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
	porting$(SLASH)hashing.c \
	porting$(SLASH)init_textures.c \
	porting$(SLASH)open_file1.c \
	porting$(SLASH)open_file2.c \
	porting$(SLASH)parse_all_audio_data.c \
	porting$(SLASH)porting_utils.c \
	porting$(SLASH)porting_utils2.c \
	porting$(SLASH)validate_sectors_data_a.c \
	porting$(SLASH)validate_sectors_data_b.c \
	porting$(SLASH)verify_hash.c \
	porting$(SLASH)write_sector_data.c \
	porting$(SLASH)write_sector_data2.c \
	porting$(SLASH)write_entity_data.c \
	porting$(SLASH)write_all_audio_data.c \
	engine$(SLASH)calc_sector_bounds.c \
	engine$(SLASH)colour_scale.c \
	engine$(SLASH)get_next_wall_tex.c \
	engine$(SLASH)get_portal_by_idx.c \
	engine$(SLASH)get_wall_height.c \
	engine$(SLASH)line_line_intersection.c \
	engine$(SLASH)line_segment_check.c \
	engine$(SLASH)recursion_checks.c \
	engine$(SLASH)scan_fov.c \
	engine$(SLASH)setup_frame.c \
	engine$(SLASH)check_distances_to_walls.c \
	update_player$(SLASH)activate_object.c \
	update_player$(SLASH)advance_story.c \
	update_player$(SLASH)check_distances.c \
	update_player$(SLASH)check_for_matching_key.c \
	update_player$(SLASH)check_if_open_portal.c \
	update_player$(SLASH)get_bullet_hit_point.c \
	update_player$(SLASH)get_ceiling_hit_point.c \
	update_player$(SLASH)get_entity_hit_point.c \
	update_player$(SLASH)get_ground_hit_point.c \
	update_player$(SLASH)get_player_hit_point.c \
	update_player$(SLASH)gravity.c \
	update_player$(SLASH)handle_doors.c \
	update_player$(SLASH)init_story.c \
	update_player$(SLASH)init_story_cutscene.c \
	update_player$(SLASH)key_input.c \
	update_player$(SLASH)key_input_toggle.c \
	update_player$(SLASH)mouse_handle.c \
	update_player$(SLASH)plr_inside.c \
	update_player$(SLASH)play_cutscene.c \
	update_player$(SLASH)player_look.c \
	update_player$(SLASH)player_move.c \
	update_player$(SLASH)player_use.c \
	update_player$(SLASH)player_use_inventory_item.c \
	update_player$(SLASH)special_movement.c \
	update_player$(SLASH)update_player.c \
	update_player$(SLASH)shooting.c \
	update_player$(SLASH)strafe_vector_along_the_wall.c \
	update_player$(SLASH)player_take_damage.c \
	update_player$(SLASH)player_place_feet_to_ground.c \
	update_player$(SLASH)reload_weapon.c \
	update_player$(SLASH)recharge_suit.c \
	update_screen$(SLASH)apply_matrices_a.c \
	update_screen$(SLASH)apply_matrices_b.c \
	update_screen$(SLASH)calculate_offsets.c \
	update_screen$(SLASH)clip_to_plane.c \
	update_screen$(SLASH)clip_to_viewport_edges.c \
	update_screen$(SLASH)draw_frame.c \
	update_screen$(SLASH)draw_horizontal_line.c \
	update_screen$(SLASH)draw_hud.c \
	update_screen$(SLASH)draw_info.c \
	update_screen$(SLASH)draw_inventory.c \
	update_screen$(SLASH)draw_object_data.c \
	update_screen$(SLASH)draw_sector.c \
	update_screen$(SLASH)draw_shapes.c \
	update_screen$(SLASH)draw_shapes2.c \
	update_screen$(SLASH)draw_tex_pixel.c \
	update_screen$(SLASH)draw_tex_triangle.c \
	update_screen$(SLASH)draw_weapon.c \
	update_screen$(SLASH)draw_wireframe.c \
	update_screen$(SLASH)init_matrices_a.c \
	update_screen$(SLASH)init_matrices_b.c \
	update_screen$(SLASH)put_pixel.c \
	update_screen$(SLASH)matrix_2d.c \
	update_screen$(SLASH)matrix_3d.c \
	update_screen$(SLASH)update_screen.c \
	update_screen$(SLASH)set_lighting.c \
	update_screen$(SLASH)death_animation_handle.c \
	utilities$(SLASH)audio_a.c \
	utilities$(SLASH)audio_b.c 	\
	utilities$(SLASH)audio_c.c 	\
	utilities$(SLASH)audio_cleanup.c \
	utilities$(SLASH)error_output.c \
	utilities$(SLASH)fps_timer.c \
	utilities$(SLASH)ft_roundf_to_grid.c \
	utilities$(SLASH)initialize_player.c \
	utilities$(SLASH)is_negative.c \
	utilities$(SLASH)mem_functions_a.c \
	utilities$(SLASH)mem_functions_b.c \
	utilities$(SLASH)pxl_alphabet.c \
	utilities$(SLASH)pxl_numbers.c \
	utilities$(SLASH)raster_queue_a.c \
	utilities$(SLASH)raster_queue_b.c \
	utilities$(SLASH)raster_queue_c.c \
	utilities$(SLASH)round_coordinates.c \
	utilities$(SLASH)setup.c \
	utilities$(SLASH)str_pxl.c \
	utilities$(SLASH)system_calls.c \
	utilities$(SLASH)swap_and_sort.c \
	utilities$(SLASH)swap_node_data.c \
	utilities$(SLASH)init_skybox.c \
	utilities$(SLASH)init_hud_elements.c \
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
	vec_math$(SLASH)vec3_g.c \
	vec_math$(SLASH)vec3_h.c \
	menu_systems$(SLASH)launch_modules.c \
	menu_systems$(SLASH)menu_inputs.c \
	menu_systems$(SLASH)menu_setups.c \
	menu_systems$(SLASH)menu_utils.c \
	menu_systems$(SLASH)menu_utils2.c \

HEADERS = \
	libft$(SLASH)libft.h \
	headers$(SLASH)doom_nukem.h \
	headers$(SLASH)audio.h \
	headers$(SLASH)colours.h \
	headers$(SLASH)drawing_functions.h \
	headers$(SLASH)engine.h \
	headers$(SLASH)entity.h \
	headers$(SLASH)events.h \
	headers$(SLASH)editor.h \
	headers$(SLASH)macros.h \
	headers$(SLASH)parser_structs.h \
	headers$(SLASH)parsing.h \
	headers$(SLASH)player.h \
	headers$(SLASH)png_parser.h \
	headers$(SLASH)porting.h \
	headers$(SLASH)program.h \
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
WIN_CFLAGS = -Wall -Wextra -O3 -g
WIN_LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lft -lpthread -lm

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
	$(MKDIR) $@$(SLASH)engine
	$(MKDIR) $@$(SLASH)entity_logic
	$(MKDIR) $@$(SLASH)utilities
	$(MKDIR) $@$(SLASH)update_player
	$(MKDIR) $@$(SLASH)update_screen
	$(MKDIR) $@$(SLASH)parsing
	$(MKDIR) $@$(SLASH)png_parser
	$(MKDIR) $@$(SLASH)porting
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
