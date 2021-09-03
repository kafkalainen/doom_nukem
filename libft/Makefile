# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/26 13:08:18 by jnivala           #+#    #+#              #
#    Updated: 2021/09/03 11:32:16 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

S = src
O = obj

ifeq ($(OS),Windows_NT)
	TARGET_SYSTEM := Windows
else
	TARGET_SYSTEM := $(shell uname -s)
	TARGET_SYSTEM := $(patsubst CYGWIN%,Cygwin,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MSYS%,MSYS,$(TARGET_SYSTEM))
	TARGET_SYSTEM := $(patsubst MINGW%,MSYS,$(TARGET_SYSTEM))
endif

ifeq ($(TARGET_SYSTEM),Windows)
	RM = del /s/q
	SLASH = \\
	MKDIR = mkdir
else
	RM = /bin/rm -rf
	SLASH = /
	MKDIR = mkdir -p
endif

SRC_LIST = \
	$(SLASH)ft_strlen.c \
	$(SLASH)ft_strdup.c \
	$(SLASH)ft_strcmp.c \
	$(SLASH)ft_strncmp.c\
	$(SLASH)ft_atoi.c \
	$(SLASH)ft_strcpy.c \
	$(SLASH)ft_strncpy.c \
	$(SLASH)ft_strcat.c \
	$(SLASH)ft_strncat.c \
	$(SLASH)ft_strlcat.c \
	$(SLASH)ft_strchr.c \
	$(SLASH)ft_strrchr.c \
	$(SLASH)ft_strstr.c \
	$(SLASH)ft_strnstr.c \
	$(SLASH)ft_isalpha.c \
	$(SLASH)ft_isdigit.c \
	$(SLASH)ft_isalnum.c \
	$(SLASH)ft_isascii.c \
	$(SLASH)ft_isprint.c \
	$(SLASH)ft_toupper.c \
	$(SLASH)ft_tolower.c \
	$(SLASH)ft_memset.c \
	$(SLASH)ft_memcpy.c \
	$(SLASH)ft_memccpy.c \
	$(SLASH)ft_memchr.c \
	$(SLASH)ft_bzero.c \
	$(SLASH)ft_memmove.c \
	$(SLASH)ft_memcmp.c \
	$(SLASH)ft_memalloc.c \
	$(SLASH)ft_memdel.c \
	$(SLASH)ft_strnew.c \
	$(SLASH)ft_strdel.c \
	$(SLASH)ft_strclr.c \
	$(SLASH)ft_putchar_fd.c \
	$(SLASH)ft_putstr_fd.c \
	$(SLASH)ft_putendl_fd.c \
	$(SLASH)ft_striter.c \
	$(SLASH)ft_striteri.c \
	$(SLASH)ft_strmap.c \
	$(SLASH)ft_strmapi.c \
	$(SLASH)ft_strequ.c \
	$(SLASH)ft_strnequ.c \
	$(SLASH)ft_strsub.c \
	$(SLASH)ft_strtrim.c \
	$(SLASH)ft_strjoin.c \
	$(SLASH)ft_strsplit.c \
	$(SLASH)ft_itoa.c \
	$(SLASH)ft_putchar.c \
	$(SLASH)ft_putstr.c \
	$(SLASH)ft_putendl.c \
	$(SLASH)ft_putnbr.c \
	$(SLASH)ft_putnbr_fd.c \
	$(SLASH)ft_lstadd.c \
	$(SLASH)ft_lstiter.c \
	$(SLASH)ft_lstmap.c \
	$(SLASH)ft_lstnew.c \
	$(SLASH)ft_lstdelone.c \
	$(SLASH)ft_lstdel.c \
	$(SLASH)ft_lstlen.c \
	$(SLASH)ft_lst_addback.c \
	$(SLASH)ft_isspace.c \
	$(SLASH)ft_strarrnew.c \
	$(SLASH)ft_strarrdel.c \
	$(SLASH)ft_strndup.c \
	$(SLASH)ft_itoa_base.c \
	$(SLASH)ft_str3darrdel.c \
	$(SLASH)ft_strlcpy.c\
	$(SLASH)ft_abs.c\
	$(SLASH)ft_atoi_base.c\
	$(SLASH)ft_count_wrds.c\
	$(SLASH)ft_nb_len.c\
	$(SLASH)ft_replace_char.c\
	$(SLASH)ft_pow_of_2.c\
	$(SLASH)ft_sqrt.c\
	$(SLASH)ft_dabs.c\
	$(SLASH)ft_cdivision.c\
	$(SLASH)ft_cmultiply.c\
	$(SLASH)ft_cpow3.c\
	$(SLASH)ft_csub.c\
	$(SLASH)ft_cabs.c\
	$(SLASH)ft_cadd.c\
	$(SLASH)ft_fmax.c\
	$(SLASH)ft_fmin.c\
	$(SLASH)ft_ftoa.c\
	$(SLASH)ft_roundf.c\
	$(SLASH)ft_ineg.c\
	$(SLASH)ft_imin.c\
	$(SLASH)ft_imax.c\
	$(SLASH)ft_fabsf.c\
	$(SLASH)ft_skipc.c\
	$(SLASH)ft_fabsf.c\
	$(SLASH)ft_signf.c\
	$(SLASH)ft_swapf.c\
	$(SLASH)ft_swapi.c\

HEADERS = ./libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = $(addprefix $S, $(SRC_LIST))
OBJ = $(SRC:$S%=$O%.o)

.PHONY: all clean fclean re cleanobj cleanobjdir

all: $(NAME)

$O:
	$(MKDIR) $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) -I. $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo Successfully created $(NAME)

cleanobj:
ifneq ($(wildcard $(OBJ)),)
	$(RM) $(wildcard $(OBJ))
endif

cleanobjdir: cleanobj
ifeq ($(TARGET_SYSTEM), Linux)
	$(RM) $O
else
	IF EXIST $O ( rd /s /q "$O" )
endif

clean: cleanobjdir
	@echo Removed object files.

fclean: clean
ifeq ($(TARGET_SYSTEM), Linux)
	$(RM) $(NAME)
else
	IF EXIST $(NAME) ( $(RM) "$(NAME)" )
endif

re: fclean all
