NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread
SRCS = check.c main.c routine.c utils_routine.c utils.c forks.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
