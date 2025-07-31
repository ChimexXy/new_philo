# NAME = philo
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
# SRC = init_data.c philo.c utils.c monitor.c philo_routine.c simulation.c \

# OBJ = $(SRC:.c=.o)

# all : $(NAME)

# $(NAME) : $(OBJ) philo.h 
# 	$(CC) $(OBJ)  -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean : 
# 	rm -rf $(OBJ)

# fclean : clean
# 	rm -rf $(NAME)

# re : fclean all


CC = clang
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -O1 -fno-omit-frame-pointer -arch x86_64
LDFLAGS = -fsanitize=thread

SRCS = philo.c init_data.c utils.c monitor.c philo_routine.c simulation.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
