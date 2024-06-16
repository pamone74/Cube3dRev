# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schennal <schennal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 20:15:22 by schennal          #+#    #+#              #
#    Updated: 2024/06/08 00:08:52 by schennal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror 
SRC = \
		cub3D.c \
		init.c \
		init1.c \
		events.c \
		events1.c \
		parsing/ft_error.c \
		parsing/p_check.c \
		parsing/p_cpy_map.c \
		parsing/p_init.c \
		parsing/p_map_utilis.c \
		parsing/p_map.c \
		parsing/p_parse.c \
		parsing/p_text_utilis.c \
		parsing/p_texture.c \
		parsing/p_wall_utilis.c \
		parsing/p_wall.c \
		parsing/parsing_utils.c \
		game.c \
		minimap.c \
		compute_ray.c \
		game_utils.c \
		wall.c \
		game1.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
LIBFT_LINK = -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(FLAGS) -Imlx $(LIBFT_INC) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_LINK) -Lmlx -lmlx -L/usr/usr/lib ./mlx/libmlx.a -lXext -lX11 -lm -lz -o $(NAME)

bonus : all

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)



