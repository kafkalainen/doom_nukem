/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main_ftoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:49:29 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:02:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*lee;

	if (argc == 3)
	{
		lee = ft_ftoa(atof(argv[1]), atoi(argv[2]));
		ft_putendl(lee);
		free(lee);
	}
	return (0);
}
