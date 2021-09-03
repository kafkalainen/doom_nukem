/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/03 16:08:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_WINDOWS_H
# define SYSCALLS_WINDOWS_H

int	_close(int fd);
int	_open(const char *pathname, int flags, int pmode);
int	_read(const int fd, const void *buffer, const unsigned int buffer_size);
int	_mkdir(const char *dirname);
int	_write(int fd, const void *buffer, unsigned int count);

#endif
