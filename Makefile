# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 16:23:53 by brunogue          #+#    #+#              #
#    Updated: 2025/02/27 17:26:03 by brunogue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC = srcs/main.c srcs/fdf.c srcs/close.c srcs/projection.c srcs/controls.c srcs/file_parser.c srcs/drawing.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -lmlx -lX11 -lXext -lm

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
