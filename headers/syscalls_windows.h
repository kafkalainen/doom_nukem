/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/22 12:46:56 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	_close(int fd);
int	_open(const char *filename, int oflag);
int	_read(int const fd, void const *buffer, unsigned const buffer_size);
