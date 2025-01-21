NAME = philo
BONUS = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = $(wildcard *_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
