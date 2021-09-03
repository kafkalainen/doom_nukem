# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_ft_strsplit.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 12:58:43 by jnivala           #+#    #+#              #
#    Updated: 2021/08/10 15:35:56 by jnivala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

test_strsplit()
{
	test_nb=$1
	str=$2
	c=$3
	answer=$4
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "Test $test_nb:"
	echo "$answer"
	if diff <(./test_strsplit $str $c | cat -e) <(echo "$answer");
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

gcc -Wall -Wextra -Werror -g test_strsplit.c src/ft_putchar.c src/ft_strlen.c src/ft_putstr.c src/ft_putendl.c src/ft_strdel.c src/ft_strsplit.c src/ft_skipc.c src/ft_strsub.c src/ft_strarrdel.c -o test_strsplit
test_strsplit '1' 'Marvin#is#strong' '#' 'Marvin$'
test_strsplit '2' 'HelloworldbHelloworld' 'b' 'Helloworld$'
