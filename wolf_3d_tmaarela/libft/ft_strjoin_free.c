/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 02:46:58 by ngontjar          #+#    #+#             */
/*   Updated: 2020/07/19 02:47:12 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates a new string large enough to hold both strings.
** The source string will be freed if non-null is returned.
** The appended string could be a string literal, won't be freed.
** Returns the new string, or NULL if an error occurs.
*/

char	*ft_strjoin_free(char *source, const char *append)
{
	char	*new;
	size_t	a;
	size_t	b;

	if (source && append)
	{
		a = ft_strlen(source);
		b = ft_strlen(append);
		if ((new = ft_strnew(a + b + 1)))
		{
			ft_strcpy(new, source);
			ft_strcpy(new + a, append);
			free(source);
		}
		return (new);
	}
	return (NULL);
}
