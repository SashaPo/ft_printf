NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRCS = src/ft_printf.c src/ft_init.c src/ft_unicode.c src/ft_handle_c.c \
       src/ft_flag_parser.c src/ft_specifiers.c src/ft_bool.c \
       src/ft_length_parser.c src/ft_handle_di.c src/ft_handle_x.c src/ft_handle_o.c \
       src/ft_handle_u.c src/ft_handle_b_for_binary.c src/ft_handle_p_for_pointer.c \
       src/ft_handle_percent_and_unknown.c src/ft_additional_functions.c src/ft_additional_functions1.c \
       src/ft_handle_str.c src/ft_additional_functions2.c src/ft_additional_functions3.c \
       src/ft_additional_functions4.c

SRCS_LIB = ft_memcmp.c 		ft_strlcat.c		ft_atoi.c \
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
		ft_itoa_base.c 		ft_itoa_base_2.c    ft_itoa_long.c \
		ft_itoa_base_long_2.c ft_itoa_ulong.c

DIR_SRCS_LIB = $(addprefix libft/, ${SRCS_LIB})
BINS = $(SRCS:.c=.o)
BINS_LIB = $(DIR_SRCS_LIB:.c=.o)

.PHONY: clean fclean re
.NOTPARALLEL: clean fclean re

all : $(NAME)

$(NAME) : $(BINS) $(BINS_LIB)
	ar rc $(NAME) $(BINS) $(BINS_LIB)
	ranlib $(NAME)

%.o:%.c
	gcc $(FLAGS) -c -o $@ -O3 $< -I includes/ -I libft/

clean:
	/bin/rm -rf $(BINS) $(BINS_LIB)
	make -C libft/ clean

fclean: clean
	/bin/rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
