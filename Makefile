# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 16:23:53 by brunogue          #+#    #+#              #
#    Updated: 2025/03/16 13:47:18 by brunogue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= lib/libft.a
MLX_LIB		= minilibx-linux/libmlx_Linux.a

SRC		= srcs/main.c srcs/fdf.c srcs/close.c srcs/projection.c srcs/controls.c srcs/file_parser.c srcs/drawing.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lX11 -lXext -lm

$(LIBFT):
	make -C lib

$(MLX_LIB):
	make -C minilibx-linux

clean:
	rm -f $(OBJ)
	make clean -C lib
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME)
	make fclean -C lib

re: fclean all

.PHONY: all clean fclean re