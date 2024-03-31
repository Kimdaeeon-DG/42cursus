# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeekim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 14:36:19 by daeekim           #+#    #+#              #
#    Updated: 2024/03/31 17:57:29 by daeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

CC = gcc
CFLAG = -Wall -Wextra -Werror 
AR  = ar rcs
RM = rm -f

ARFLAGS  = crs

INCLUDES = ./ft_printf.h

SRCS =	ft_printf.c /prt_hexa.c/prt_int.c/prt_ptr.c/prt_str.c/prt_unsigned.c/ft_strlen.c/ft_putchar_fd.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re : clean all

 .PHONY: all clean fclean re
