/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:49:38 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/12 18:48:27 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

char				*ft_strnstr(const char	*big, const char *little, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
size_t				ft_strlcat(char *dest, const char *app, size_t dstsize);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				*ft_memmove(void *dest, const void *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strncpy (char *dst, const char *src, size_t n);
char				*ft_strncat(char *dest, const char *app, size_t n);
char				*ft_strstr(const char *where, const char *tofind);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *memptr, int c, size_t len);
int					ft_strcmp(const char *str1, const char *str2);
void				ft_del(void *content, size_t content_size);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_memset(void *memory, int ch, size_t n);
char				*ft_strmap(char const *s, char(*f)(char));
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strcat(char *dest, const char *app);
char				*ft_strcpy(char *dst, const char *src);
void				ft_striter(char *s, void (*f)(char *));
char				**ft_strsplit(char const *s, char c);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_strrchr(const char *str, int c);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strchr(const char *str, int c);
void				ft_putchar_fd(char c, int fd);
void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *str);
char				*ft_strtrim(char const *s);
void				ft_putendl(char const *s);
void				*ft_memalloc(size_t size);
void				ft_putstr(char const *s);
char				*ft_strnew(size_t size);
void				ft_swap(int *a, int *b);
int					ft_atoi(const char *s);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
int					ft_putchar(char c);
int					ft_isalnum(int ch);
int					ft_isalpha(int ch);
int					ft_isascii(int ch);
int					ft_isdigit(int ch);
int					ft_isprint(int ch);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
void				ft_strclr(char *s);
void				ft_putnbr(int n);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
char				*ft_itoa_base_2(int value, int base);
char				*ft_itoa_long(long long int n);
char				*ft_itoa_base_long_2(long long int value, int base);
char				*ft_itoa_ulong(unsigned long long int n);
char				*itoa_u(unsigned long long int value, int base, char type);
char				*itoa_signed(long long int value, int base, char type);
char				*ft_itoa_double_prec(double n, int prec);
char				*ft_dtoa(double n);

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
int					ft_lst_size(t_list *begin_list);
void				ft_lstpush_b(t_list **begin, t_list *new);
void				ft_lstclear(t_list **begin_list);

#endif
