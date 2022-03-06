SRCS =	sources/main.c\
		sources/utils.c


OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -lpthread
NAME		= philo

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} -o ${NAME} ${OBJS} -lpthread 

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all