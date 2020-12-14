NAME = wolf3d

# SOURCES =	$(wildcard *.c)
SOURCES =	main.c \
			ft_clear_buffer.c \
			ft_put_pixel.c \
			ft_draw_line.c \
			ft_draw_box.c \
			ft_draw_wall.c \
			ft_new_image.c \
			cast_ray.c \
			color.c \
			vec2_basics.c \
			vec2.c \
			render.c \
			input.c \
			input_events.c

OBJECTS = $(subst .c,.o,$(SOURCES))

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra
LINKS = -I libft -L libft -l ft \
		-I /usr/local/include -L /usr/local/lib -l mlx \
		-framework OpenGL -framework Appkit

LINUX_LINKS = -I libft -L libft -l ft \
		-I /usr/local/include -L /usr/local/lib -l mlx \
		-lm -lXext -lX11

MSG = \033[38;5;214m
END = \033[0m

.PHONY: all clean fclean re linux

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(OBJECTS) -o $(NAME) $(FLAGS) $(LINKS)
	@echo "$(MSG)Done!$(END)"

linux: $(OBJECTS)
	@gcc $(OBJECTS) -o $(NAME) $(FLAGS) $(LINUX_LINKS)
	@echo "$(MSG)Done!$(END)"

$(OBJECTS): $(LIBFT) $(SOURCES)
	@echo "$(MSG)Compiling...$(END)"
	@gcc $(FLAGS) -c $(SOURCES)

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@rm -f $(OBJECTS)
	@echo "$(MSG)Objects removed!$(END)"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(MSG)Targets removed!$(END)"

re: fclean all
