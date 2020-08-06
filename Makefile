.PHON: all clean fclean re

NAME =	fractol
SRCS =	main2.c \
	keyboard.c \
	algs.c\
	color.c\
	helpers.c

OBJS = $(SRCS:.c=.o)
HEADER_DIR = src/
CC = gcc
FLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit libft/libft.a -lpthread -lm
HEADER = mlx.h
all: $(NAME)
$(NAME):
	$(CC) $(SRCS) $(FLAGS) -o $(NAME) $(EXTRA_FLAGS)
clean:
	/bin/rm -f src/*.o
	/bin/rm -f src/*.gch
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all

