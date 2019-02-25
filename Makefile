# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achepurn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/21 21:48:41 by achepurn          #+#    #+#              #
#    Updated: 2018/03/21 21:48:44 by achepurn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAG = #-Wall -Wextra -Werror
NAME = fractol
INCL = fractol.h
SRC = 	main.c \
		fractols.c \
		hooks.c
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a
LIB_LNK = -L libft/ -lft
MLX = minilibx_macos/libmlx.a
MLX_LNK = -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIB) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LIB_LNK) -lpthread $(MLX_LNK) -o $(NAME)

%.o: %.c $(INCL)
	$(CC) -c $(CFLAG) $< -o $@

clean:
	make -C libft/ clean
	rm -rf $(OBJ)
	make -C minilibx_macos clean

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)
	make -C minilibx_macos fclean

$(MLX):
	make -C minilibx_macos

$(LIB):
	make -C libft

re: fclean all