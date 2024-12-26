NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = src/main.c \
       src/builtins/echo.c \
       src/builtins/cd.c \
       src/builtins/pwd.c \
       src/builtins/export.c \
       src/builtins/unset.c \
       src/builtins/env.c \
       src/builtins/exit.c \
       src/parser/parser.c \
       src/parser/tokenizer.c \
       src/executor/executor.c \
       src/signals/signals.c \
       src/utils/env_utils.c \
       src/utils/string_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
