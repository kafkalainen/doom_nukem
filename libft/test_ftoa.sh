# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_ftoa.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 12:58:43 by jnivala           #+#    #+#              #
#    Updated: 2021/03/29 10:06:41 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

test_main_ftoa()
{
	test_nb=$1
	nb=$2
	precision=$3
	answer=$4
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "Test $test_nb:"
	echo "$answer"
	if diff <(./test_ftoa $nb $precision | cat -e) <(echo "$answer");
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

gcc -Wall -Wextra -Werror -g test_main_ftoa.c ft_ftoa.c ft_itoa.c ft_strjoin.c ft_strlen.c ft_strcpy.c ft_strcat.c ft_putendl.c ft_putchar.c ft_putstr.c ft_roundf.c -o test_ftoa
test_main_ftoa '1' '0.000045' '5' '0.00005$'
test_main_ftoa '2' '-0.000045' '5' '-0.00005$'
test_main_ftoa '3' '0.000045' '6' '0.000045$'
test_main_ftoa '4' '0' '1' '0.0$'
test_main_ftoa '5' '7' '1' '7.0$'
test_main_ftoa '6' '-1.666' '3' '-1.666$'
