/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_linux.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:44:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/22 12:46:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	close(int fd);
int	open(const char *filename, int oflag);
int	read(int const fd, void const *buffer, unsigned const buffer_size);
