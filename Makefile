# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 16:23:53 by brunogue          #+#    #+#              #
#    Updated: 2025/02/01 17:39:05 by brunogue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBFT = lib/libft.a
MLX = ../minilibx-linux

SRC = srcs/main.c srcs/fdf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L$(MLX) -lmlx -lX11 -lXext -lm

$(LIBFT):
	make -C lib

clean:
	rm -f $(OBJ)
	make clean -C lib

fclean: clean
	rm -f $(NAME)
	make fclean -C lib

re: fclean all
