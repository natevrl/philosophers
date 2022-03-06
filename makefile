SRCS =	sources/main.c\
		sources/utils.c


OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I include -lpthread
NAME		= philo

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) ${CFLAGS} -o ${NAME} ${OBJS} 

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
