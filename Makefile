NAME = fillit

CFLAGS = -I includes/

CC = gcc

SRC_C = 	main.c \
			ft_putstr.c \
			ft_putendl_fd.c \
			ft_strlen.c

INCLUDE_H = libft.h \
			fillit.h

SRC = $(addprefix ./srcs/, $(SRC_C))

all: $(NAME)

$(NAME) :
			$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
		rm -f $(SRC_O)

fclean: clean
		rm -f $(NAME)

re : fclean all
