SRCS =	main.c								\
		srcs/new_surface_to_texture.c		\
		srcs/vec2_a.c						\
		srcs/vec2_b.c

all: 
	gcc $(SRCS) -o play -I include -L lib -l SDL2-2.0.0
