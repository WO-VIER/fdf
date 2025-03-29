# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/29 17:29:51 by vwautier          #+#    #+#              #
#    Updated: 2025/03/29 17:39:24 by vwautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources
SRCS = fdf.c \
machin.c \
vue.c \
setup.c \
control.c

OBJS = $(SRCS:.c=.o)

# Dossiers des bibliothèques
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
GNL_DIR = gnl

# Bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
GNL = $(GNL_DIR)/libgnl.a

# Headers
INCLUDES = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Options de liaison
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L$(GNL_DIR) -lgnl -lXext -lX11 -lm

# Règles principales
all: $(NAME)

$(LIBFT): @make -C $(LIBFT_DIR)

$(MLX): @make -C $(MLX_DIR)

$(GNL): @make -C $(GNL_DIR)

$(NAME): $(LIBFT) $(MLX) $(GNL) $(OBJS) $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c fdf.h $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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