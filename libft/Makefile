# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opokusyn <opokusyn@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 15:39:10 by opokusyn          #+#    #+#              #
#    Updated: 2018/03/12 18:49:58 by opokusyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FILES = ft_memcmp.c 		ft_strlcat.c		ft_atoi.c \
		ft_memcpy.c 		ft_strlen.c			ft_bzero.c \
		ft_strncat.c 		ft_memmove.c		ft_strncmp.c \
		ft_isalnum.c		ft_strncpy.c		ft_memdel.c \
		ft_isalpha.c		ft_memset.c			ft_strnstr.c \
		ft_isascii.c		ft_strrchr.c		ft_memalloc.c \
		ft_isdigit.c		ft_strcat.c			ft_strstr.c \
		ft_isprint.c		ft_strchr.c			ft_tolower.c \
		ft_memccpy.c		ft_strcmp.c			ft_toupper.c \
		ft_strcpy.c 		ft_memchr.c			ft_strdup.c \
		ft_putchar.c		ft_putchar_fd.c		ft_putstr.c \
		ft_putstr_fd.c		ft_putendl.c		ft_putendl_fd.c \
		ft_strnew.c			ft_strdel.c			ft_strclr.c \
		ft_striter.c		ft_striteri.c		ft_strmap.c \
		ft_strmapi.c		ft_strequ.c			ft_strnequ.c \
		ft_strsub.c			ft_strjoin.c		ft_strtrim.c \
		ft_putnbr.c			ft_putnbr_fd.c		ft_strsplit.c \
		ft_itoa.c			ft_lstnew.c			ft_lstdelone.c \
		ft_lstdel.c			ft_lstadd.c			ft_lstiter.c \
		ft_lstmap.c			ft_lstpush_b.c		ft_lstclear.c \
		ft_lst_size.c		ft_swap.c			ft_del.c \
		ft_itoa_base.c 		ft_itoa_base_2.c	ft_itoa_long.c \
		ft_itoa_base_long_2.c ft_itoa_ulong.c
OFILES = $(FILES:%.c=%.o)

FLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC)  $(FLAGS) $(FILES) -I Libft
	ar rc $(NAME) $(OFILES)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OFILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
