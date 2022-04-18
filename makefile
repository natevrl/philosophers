SRCS =	sources/main.c\
		sources/utils.c\
		sources/actions.c\
		sources/parsing.c\
		sources/initialisations.c\

OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
TFLAGS		= -lpthread
INCLUDE		= ./include
NAME		= philo

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} -o ${NAME} ${OBJS} -I ${INCLUDE} ${TFLAGS}

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all