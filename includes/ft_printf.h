/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:37:52 by opokusyn          #+#    #+#             */
/*   Updated: 2018/03/09 20:39:08 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum		e_length
{
	none,
	t,
	l,
	ll,
	h,
	hh,
	j,
	z
}					t_length;

typedef struct		s_flags
{
	char			minus;
	char			plus;
	int				dot;
	int				implicit_dot;
	char			space;
	char			star;
	char			zero;
	char			hash;
	size_t			width;
	t_length		len;
}					t_flags;

typedef struct		s_pf
{
	char			*spec;
	size_t			speclen;
	t_flags			flags;
	char			type;
}					t_pf;

unsigned long long	fetch_unsigned_arg(t_pf *pf, va_list args);
int					ft_printf(const char *str, ...);
t_pf				*ft_init(t_pf *pf);
int					map_specifier(t_pf *pf, va_list args);
int					ft_handle_o(t_pf *pf, va_list args);
int					ft_handle_c(t_pf *pf, va_list args);
int					ft_handle_p(t_pf *pf, va_list args);
int					ft_handle_b(t_pf *pf, va_list args);
ssize_t				ft_handle_x(t_pf *pf, va_list args);
char				*ft_itoa_long_prec(long long int n, int prec);
char				*ft_unicode(unsigned int un);
char				*ft_handle_unistr(unsigned int nbrs);
int					ft_handle_percent(t_pf *pf, va_list args);
int					ft_handle_u(t_pf *pf, va_list args);
int					ft_handle_str(t_pf *pf, va_list args);
int					ft_handle_unknown(t_pf *pf, va_list args);
void				parse_specifier(t_pf *pf);
int					ft_handle_di(t_pf *pf, va_list args);
long long			fetch_signed_arg(t_pf *pf, va_list args);
void				parse_prec(t_pf *pf);
void				parse_length(t_pf *pf);
void				parse_width(t_pf *pf);
void				parse_flags(t_pf *pf);
void				parse_implicit_dot(t_pf *pf);
size_t				cut_specifier(const char *format, t_pf *pf);
size_t				specifier_len(const char *format);
t_bool				is_valid_type(char c);
int					free_deluxe(void **ad);
int					ft_get_exception(t_pf *pf);
t_bool				is_length(char c);
t_bool				is_flag(char c);
int					f(void **ad);
t_bool				has_conversion_type(const char *format);
size_t				ft_exception_case(char *exp, size_t lenp);
int					ft_two_cases(t_pf *pf, int leno);
int					ft_hc(int ifdot, int len, t_pf *pf);
int					ft_res1(t_pf *pf, int leno);
int					ft_h_o(t_pf *pf, size_t len_ex, unsigned long long octal);
int					res(t_pf *pf, int leno, unsigned long long octal, char *ex);
int					ft_res_part(t_pf *pf, int leno, size_t len_ex, char *ex);
int					ft_two_cased(t_pf *pf);
int					ft_first_diff(t_pf *pf, int len, char *expanded);
int					ft_s_dif(t_pf *pf, int len, char *expanded, int difference);
int					ft_test(t_pf *pf, int len, char *expanded);
int					ft_zero_arg(t_pf *pf, int len);
size_t				ft_ifwidth(t_pf *pf, size_t strlen);
int					ft_ifdiffer(t_pf *pf, char *count, int slen, size_t strlen);
char				*ft_uni_code(char *count, unsigned int *str);
int					ft_uni_code1(unsigned int *str);
size_t				ft_lencheck(t_pf *pf, int onelen, size_t strlen);
size_t				ft_strch(t_pf *pf, char *count, int onelen, size_t strlen);
int					ft_respart(t_pf *pf, int len, char *expanded);
int					ft_dresult(t_pf *pf, int len, char *expanded);
int					ft_lenminus(t_pf *pf, int len, char *expanded);
int					ft_lenplus(t_pf *pf, int len, char *expanded);
int					ft_lenwidth(t_pf *pf, int len, char *expanded, int dif);
int					ft_inside(t_pf *pf, int len, char *expanded, int dif);
int					ft_miniret(t_pf *pf, int len, char *expanded);
int					ft_ret(t_pf *pf, int len, char *expanded);

#endif
