/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/27 14:13:12 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_WINDOWS_H
# define SYSCALLS_WINDOWS_H

int	_close(int fd);
int _open(const char *pathname, int flags, int pmode);
int	_read(int const fd, void const *buffer, unsigned const int buffer_size);
#endif
