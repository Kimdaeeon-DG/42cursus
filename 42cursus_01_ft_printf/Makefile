# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeekim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 15:42:50 by daeekim           #+#    #+#              #
#    Updated: 2024/04/07 14:10:45 by daeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
 
NAME = libftprintf.a
 
SRC =  ft_printf.c prt_hexa.c prt_int.c prt_ptr.c prt_str.c prt_unsigned.c ft_strlen.c ft_putchar_fd.c

all: $(NAME)
 
CC = gcc

CFLAGS = -Wall -Wextra -Werror
 
OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(AR) -crs  ${NAME} ${OBJS}
 
clean:
	$(RM) $(OBJS)
 
fclean: clean
	$(RM) $(NAME)
 
re: fclean all
 
 .PHONY: all clean fclean re
