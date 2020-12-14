/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:14:44 by ngontjar          #+#    #+#             */
/*   Updated: 2020/08/24 19:31:26 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>

/*
** uintptr_t
*/

# ifdef __linux__

#  include <stdint.h>
# endif

/*
** Forbidden, use snippets instead:
** # define ABS(value) (((value) < 0) ? -(value) : (value))
** # define MAX(v1, v2) ((v1) > (v2) ? (v1) : (v2))
** # define MIN(v1, v2) ((v1) < (v2) ? (v1) : (v2))
*/

# define BUFF_SIZE 16

# define MAX_INT (2147483647)
# define MIN_INT (-MAX_INT - 1)
# define MAX_UINT ((unsigned int)-1)
# define MAX_ULONG ((unsigned long)-1)
# define MAX_ULLONG ((unsigned long long)-1)

# define PI (3.1415926535897932384626433832795f)
# define PI_BY_TWO (1.5707963267948966192313216916398f)
# define TWO_PI (6.283185307179586476925286766559f)
# define RAD_TO_DEG (57.295779513082320876798154814105f)
# define DEG_TO_RAD (0.017453292519943295769236907684886f)

# define TRUE (1)
# define FALSE (0)
# define ERROR (-1)
# define NOT_FOUND (-1)

# define TX_NORMAL  "\x1B[0m"
# define TX_BOLD    "\x1B[1m"
# define TX_UNDER   "\x1B[4m"

# define FG_BLACK   "\x1B[30m"
# define FG_RED     "\x1B[31m"
# define FG_GREEN   "\x1B[32m"
# define FG_YELLOW  "\x1B[33m"
# define FG_BLUE    "\x1B[34m"
# define FG_MAGENTA "\x1B[35m"
# define FG_CYAN    "\x1B[36m"
# define FG_WHITE   "\x1B[37m"

# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(const void *content, size_t content_size);
void			ft_lstadd(t_list **head, t_list *new);
void			ft_lstadd_back(t_list *head, t_list *new);

void			ft_lstdelone(t_list **link, void (*del)(void *, size_t));
void			ft_lstdel(t_list **head, void (*del)(void *, size_t));
void			ft_lstfree(void *content, size_t content_size);

void			ft_lstiter(t_list *link, void (*func)(t_list *link));
t_list			*ft_lstmap(t_list *head, t_list *(*func)(t_list *link));

/*
** Memory free
*/

void			ft_memdel(void **ptr);
void			ft_strdel(char **str);

/*
** Memory allocation
*/

void			*ft_realloc(void *ptr, size_t size);
void			*ft_memalloc(size_t size);
char			*ft_strnew(size_t size);
char			*ft_strdup(const char *str);
char			*ft_strsub(const char *str, unsigned int start, size_t len);
char			*ft_strjoin(const char *dst, const char *str);
char			*ft_strjoin_free(char *source, const char *append);
char			*ft_strmap(const char *str, char (*f)(char));
char			*ft_strmapi(const char *str, char (*f)(unsigned int, char));
char			*ft_strtrim(const char *str);
char			**ft_strsplit(const char *str, char c);
int				*ft_range(int min, int max);
char			*ft_itoa(long long number);
char			*ft_itoa_base(long long number, int base);
char			*ft_ftoa(long double floating, unsigned char precision);
int				ft_get_next_line(const int fd, char **out);

/*
** Memory modify, no allocation
*/

void			*ft_memset(void *dst, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);

/*
** Memory checking
*/

void			*ft_memchr(const void *dst, int c, size_t n);
int				ft_memcmp(const void *dst, const void *src, size_t n);

/*
** Standard output
*/

size_t			ft_putchar(char c);
void			ft_putnbr(int nbr);

size_t			ft_putstr(const char *str);
size_t			ft_putstrn(const char *str, size_t n);
size_t			ft_putstrn_nulls(const char *str, const char c, size_t n);

size_t			ft_putendl(const char *str);
size_t			ft_putnotice(const char *str, const char *fg, const char *bg);

void			ft_print2dstr(char **array, size_t count);
void			ft_printlst(t_list *head);
void			ft_printlst_endl(t_list *head);
void			ft_print_memory(const void *addr, size_t size);

/*
** File output
*/

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *str, int fd);
void			ft_putendl_fd(const char *str, int fd);
void			ft_putnbr_fd(int nbr, int fd);

/*
** Char checking
*/

int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_isspace(int c);
int				ft_atoi(const char *str);
long			ft_atoi_base(const char *str, int base);
int				check_base_prefix(const char *str);

/*
** String checking
*/

size_t			ft_strclen(const char *str, int c);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *str1, const char *str2);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				ft_strequ(const char *str1, const char *str2);
int				ft_strnequ(const char *str1, const char *str2, size_t n);
char			*ft_strrchr(const char *str, int c);
char			*ft_strchr(const char *str, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);

/*
** String modify, no allocation
*/

void			ft_strclr(char *str);
void			ft_bzero(void *dst, size_t n);
char			*ft_strcpy(char *dst, const char *str);
char			*ft_strncpy(char *dst, const char *str, size_t len);
size_t			ft_strlcpy(char *dst, const char *str, size_t n);
char			*ft_strcat(char *dst, const char *str);
char			*ft_strncat(char *dst, const char *str, size_t n);
size_t			ft_strlcat(char *dst, const char *str, size_t dstsize);
void			ft_striter(char *str, void (*func)(char *));
void			ft_striteri(char *str, void (*func)(unsigned int, char *));
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_strrev(char *str);

/*
** Math, no allocation
*/

unsigned int	ft_lcm(unsigned int a, unsigned int b);
unsigned int	ft_hcf(unsigned int a, unsigned int b);
unsigned int	ft_sqrt_int(unsigned int number);
unsigned int	ft_prime_nfactors(unsigned int number);

unsigned int	ft_issquare_int(unsigned int number);
unsigned int	ft_isprime(unsigned int number);

int				ft_numlen(long number);
int				ft_numlen_ul(unsigned long number);
int				ft_numlen_ull(unsigned long long number);
int				ft_numlen_base(long number, int base);

double			ft_clamp(double in, double low, double high);

/*
** Math, allocation
*/

unsigned int	*ft_prime_factors(unsigned int number);

#endif
