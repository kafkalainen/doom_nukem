/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:31:59 by jnivala           #+#    #+#             */
/*   Updated: 2020/07/16 15:14:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include "./libft.h"

static int	ft_return_leftover_nl(char **line, char **left_over)
{
	char		*temp;
	char		*newline_detected;

	newline_detected = ft_strchr(*left_over, '\n');
	if (newline_detected)
	{
		if (!(*line = ft_strndup(*left_over, newline_detected - *left_over)))
			return (-1);
		temp = *left_over;
		if (!(*left_over = ft_strdup(++newline_detected)))
			return (-1);
		if (ft_strlen(*left_over) == 0)
			ft_strdel(left_over);
		ft_strdel(&temp);
		return (1);
	}
	return (0);
}

static int	ft_return_nl_after_read(char *buf, char **line, char **left_over)
{
	char		*temp;
	char		*next_nl;

	next_nl = ft_strchr(buf, '\n');
	if (*left_over)
	{
		if (!(temp = ft_strndup(buf, next_nl - buf)))
			return (-1);
		if (!(*line = ft_strjoin(*left_over, temp)))
		{
			ft_strdel(left_over);
			ft_strdel(&temp);
			return (-1);
		}
		ft_strdel(left_over);
		ft_strdel(&temp);
	}
	else
	{
		if (!(*line = ft_strndup(buf, next_nl - buf)))
			return (-1);
	}
	if (ft_strlen(++next_nl) > 0)
		*left_over = ft_strdup(next_nl);
	return (1);
}

static int	ft_there_is_no_nl(char *buf, char **left_over)
{
	char		*temp;

	if (*left_over)
	{
		if (!(temp = ft_strjoin(*left_over, buf)))
			return (-1);
		ft_strdel(left_over);
		*left_over = ft_strdup(temp);
		ft_strdel(&temp);
	}
	else
	{
		if (!(*left_over = ft_strdup(buf)))
			return (-1);
	}
	return (0);
}

static int	ft_handle_nl_returns(char *buf, char **line, char **left_over)
{
	int			ret;
	char		*next_nl;

	ret = 0;
	next_nl = ft_strchr(buf, '\n');
	if (next_nl)
		ret = ft_return_nl_after_read(buf, line, left_over);
	else
		ret = ft_there_is_no_nl(buf, left_over);
	if (ret == -1)
		ft_strdel(left_over);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*left_over;

	ret = 0;
	if (fd == -1 || !line)
		return (-1);
	if (left_over && (ret = ft_return_leftover_nl(line, &left_over) != 0))
		return (ret);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((ret = ft_handle_nl_returns(buf, line, &left_over)) != 0)
			return (ret);
	}
	if (left_over && ft_strlen(left_over) > 0)
	{
		if (!(*line = ft_strdup(left_over)))
			return (-1);
		ft_strdel(&left_over);
		return (1);
	}
	ft_strdel(&left_over);
	return (ret);
}
