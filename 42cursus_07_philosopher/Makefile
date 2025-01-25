# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 15:52:50 by daeekim           #+#    #+#              #
#    Updated: 2025/01/25 15:52:51 by daeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CFLAGS		=	-Wall -Wextra -Werror -I -g # -g3 -fsanitize=address

FILE		=	main.c \
				actions.c \
				clean_exit.c \
				utils.c


OBJ_DIR		=	./obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(patsubst %.c,%.o,$(FILE)))

all: $(NAME)

$(OBJ_DIR)/%.o	:  %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)			: $(OBJS)
	cc $(CFLAGS) -o $@ $^ -lpthread

clean			:
	rm -rf $(OBJ_DIR)

fclean			: clean
	rm -f $(NAME)

re				: fclean all

.PHONY: clean fclean all re
