/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:35:57 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/07 16:03:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct s_complex
{
	double			re;
	double			im;
}				t_complex;

typedef const char	t_c_char;

char				***ft_3dstrarrdel(char ****a3d, size_t z, size_t y);
int					ft_atoi(const char *nptr);
int					ft_atoi_base(const char *nptr, int base);
int					ft_abs(int i);
void				ft_bzero(void *s, size_t n);
double				ft_cabs(t_complex c);
t_complex			ft_cadd(t_complex x, t_complex y);
t_complex			ft_cdivision(t_complex x, t_complex y);
t_complex			ft_cmultiply(t_complex x, t_complex y);
t_complex			ft_cpow3(t_complex z);
t_complex			ft_csub(t_complex x, t_complex y);
size_t				ft_count_wrds(const char *s, int d);
double				ft_dabs(double i);
float				ft_fabsf(float i);
float				ft_fmax(float a, float b);
float				ft_fmin(float a, float b);
char				*ft_ftoa(float nb, int precision);
int					ft_imin(int a, int b);
int					ft_imax(int a, int b);
int					ft_ineg(int nb);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lst_addback(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_lstlen(t_list **alst);
void				*ft_memalloc(size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_memstr(const char *haystack, const char *needle,
						size_t size);
int					ft_nb_len(int value, int base);
double				ft_pow_of_2(double base, double exponent);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
size_t				ft_replace_char(char *s, int c, int rep);
float				ft_roundf(float nb, int prec);
int					ft_signf(float nb);
char				*ft_skipc(char *str, char c);
double				ft_sqrt(double base);
char				**ft_strarrnew(size_t arr_len, char const *str);
char				**ft_strarrdel(char ***as, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strcat(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strncat(char *dest, const char *src, size_t n);
void				ft_strclr(char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strncpy(char *dest, const char *src, size_t n);
void				ft_strdel(char **as);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(t_c_char *big, t_c_char *little, size_t len);
char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swapi(int *i0, int *i1);
void				ft_swapf(float *f0, float *f1);
int					ft_toupper(int c);
int					ft_tolower(int c);
#endif
