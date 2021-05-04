/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls_windows.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:45:10 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/04 15:58:53 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	_close(int fd);
int _open(const char *pathname, int flags, int pmode);
int	_read(int const fd, void const *buffer, unsigned const buffer_size);
