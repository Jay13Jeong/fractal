NAME	= fractol
SRCS	= srcs/main.c srcs/draw.c srcs/event.c srcs/f2a.c
OBJS	= ${SRCS:.c=.o}
LIBFT_A = libft/libft.a
HEADER  = -I./includes/
LIBX	= minilibx_opengl_20191021
CC	  = gcc
CFLAGS  = -Wall -Wextra -Werror

all:	${NAME}

bonus:  ${NAME}

%.o: %.c
	$(CC) ${CFLAGS} ${HEADER} -Imlx -c $< -o $@

$(NAME):	${OBJS}
	make -C libft
	$(CC) ${LIBFT_A} ${OBJS} -lmlx -L$(LIBX) -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make clean -C libft
	rm -f ${OBJS}
fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
