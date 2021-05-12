/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_linux.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:44:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/27 14:13:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSCALLS_LINUX_H
# define SYSCALLS_LINUX_H
#  include <sys/types.h>

int	close(int fd);
int open(const char *pathname, int flags, mode_t mode);
int	read(int const fd, void const *buffer, unsigned const int buffer_size);
#endif
