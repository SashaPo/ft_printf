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

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_length
{
	none,
	t,
	l,
	ll,
	h,
	hh,
	j,
	z
}			t_length;

typedef struct	s_flags
{
	char		minus;
	char		plus;
	int			dot;
	char		space;
	char		zero;
	char		hash;
	size_t		width;
	t_length	len;
}				t_flags;

typedef struct	s_pf
{
	va_list		*args;
	char		*spec;
    size_t      speclen;
	t_flags 	flags;
	char		type;
}				t_pf;

int  ft_printf(const char *str, ...);
t_pf	*ft_init(t_pf *pf);
int		map_specifier(t_pf *pf, va_list args);
int  get_oO(t_pf *pf, va_list args);
int  get_cC(t_pf *pf, va_list args);
int  get_p(t_pf *pf, va_list args);
ssize_t  get_xX(t_pf *pf, va_list args);
char			*ft_itoa_long_prec(long long int n, int prec);

int  get_percent(t_pf *pf, va_list args);
int  get_uU(t_pf *pf, va_list args);
int  get_sS(t_pf *pf, va_list args);
int  get_unknown(t_pf *pf, va_list args);
void	parse_specifier(t_pf *pf);
int	get_dDi(t_pf *pf, va_list args);
unsigned long long fetch_unsigned_arg(t_pf *pf, va_list args);
long long fetch_signed_arg(t_pf *pf, va_list args);
void	parse_prec(t_pf *pf);
void	parse_length(t_pf *pf);
void	parse_width(t_pf *pf);;
void	parse_flags(t_pf *pf);
size_t	cut_specifier(const char *format, t_pf *pf);
size_t	specifier_len(const char *format);
t_bool is_valid_type(char c);

#endif
