# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/29 17:29:51 by vwautier          #+#    #+#              #
#    Updated: 2025/04/08 15:29:10 by vwautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror


SRCS = fdf.c rotate.c util_vue.c vue.c setup.c control.c board.c board_util.c board_free.c
OBJS = $(SRCS:.c=.o)


LIBFT_DIR = libft
MLX_DIR = minilibx-linux
GNL_DIR = gnl


LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
GNL = $(GNL_DIR)/gnl.a


INCLUDES = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)


LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(GNL) -lXext -lX11 -lm


all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(GNL):
	make -C $(GNL_DIR)

$(NAME): $(LIBFT) $(MLX) $(GNL) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c fdf.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean 
	make -C $(GNL_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re