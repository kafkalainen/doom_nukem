/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/26 15:37:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_WINDOWS_H
# define SYSCALLS_WINDOWS_H

int	_close(int fd);
int	_open(const char *filename, int oflag);
int	_read(int const fd, void const *buffer, unsigned const int buffer_size);
#endif
