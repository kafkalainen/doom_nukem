/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/12 16:15:35 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_WINDOWS_H
# define SYSCALLS_WINDOWS_H

int	_close(int fd);
int _open(const char *pathname, int flags, int pmode);
int	_read(int const fd, void const *buffer, unsigned const buffer_size);
int	_mkdir(const char *dirname);
int _write(int fd, const void *buffer, unsigned int count);

#endif