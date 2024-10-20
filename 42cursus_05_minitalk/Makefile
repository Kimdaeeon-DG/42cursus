# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 13:24:41 by daeekim           #+#    #+#              #
#    Updated: 2024/08/28 13:25:34 by daeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

SER = src/server.c
CLI = src/client.c

UTILS = src/minitalk_utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all : $(SERVER) $(CLIENT)

$(SERVER) : $(SER) $(UTILS) 
	$(CC) $(CFLAGS) $^ -o $@
$(CLIENT) : $(CLI) $(UTILS) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@$(RM) *.o

fclean:
	@$(RM) *.o  $(SERVER) $(CLIENT)

re: 
	make fclean
	make all

.PHONY: all clean fclean all
