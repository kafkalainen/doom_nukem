/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_linux.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:44:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/10 12:51:50 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	close(int fd);
int	open(const char *filename, int oflag);
int	read(int const fd, void const *buffer, unsigned const buffer_size);
int	mkdir(const char *pathname, mode_t mode);
