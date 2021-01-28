/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:04 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/22 14:01:54 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** Libft functions (recoded libc functions)
*/

int				ft_numlen(long number);
char			*ft_itoa(long long number);
char			*ft_ftoa(long double num, int prec, int dot);
int				ft_atoi(const char *str);

size_t			ft_strlen(const char *str);
size_t			ft_strclen(const char *str, int c);
void			ft_strdel(char **p);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strcpy(char *dst, const char *str);
int				ft_strcmp(const char *str1, const char *str2);
char			*ft_strsub(const char *str, unsigned int start, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strcat(char *dst, const char *str);
char			*ft_strjoin(const char *s1, const char *s2);

void			*ft_memset(void *dst, int c, size_t n);
void			ft_memdel(void **p);

int				ft_get_next_line(const int fd, char **out);
void			ft_putendl_fd(char const *s, int fd);

#endif
