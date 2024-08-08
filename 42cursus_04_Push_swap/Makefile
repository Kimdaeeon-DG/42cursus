# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeekim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 16:12:42 by daeekim           #+#    #+#              #
#    Updated: 2024/07/22 15:06:57 by daeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar

SRCS = deque.c main.c push_pop.c sortings.c sandglass.c\
	util/push.c util/rotate.c util/r_rotate.c util/swap.c util/value.c\
	libft/ft_split.c libft/ft_atoi.c libft/ft_isdigit.c libft/ft_strlen.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
		   ${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
