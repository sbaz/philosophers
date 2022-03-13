NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

SRCS = main.c\
	  philo.c\
	  utils.c\
	  time.c\
	  routine.c\
	  error.c\

OBJ =  $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re