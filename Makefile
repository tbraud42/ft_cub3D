# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 18:10:28 by tbraud            #+#    #+#              #
#    Updated: 2025/01/18 12:47:06 by brguicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D

SRC_DIR	:= src/
OBJ_DIR	:= obj/

CC		:= gcc
CFLAGS	:= -Wextra -Wall -Werror -g

INCLUDE	:= -I ./include

SRC		:=	src/main.c \
			src/init.c \
			src/error/ft_error.c \
			src/error/parsing_error.c \
			src/player/ft_direction.c \
			src/player/ft_mouse.c \
			src/player/ft_display.c \
			src/player/ft_move.c \
			src/player/ft_position.c \
			src/player/ft_raycasting.c \
			src/player/put_pixel.c \
			src/parsing/ft_parse.c \
			src/parsing/ft_get_colors.c \
			src/parsing/ft_get_texture_path.c \
			src/parsing/ft_verif_map.c \
			src/parsing/verif_map_utils.c \
			src/utils/ft_split.c \
			src/utils/ft_utils.c \
			src/utils/get_next_line_utils.c \
			src/utils/get_next_line.c \
			src/utils/ft_putstr_fd.c \
			src/utils/len.c \
			src/utils/alloc.c \
			src/utils/free.c

OBJ		:= $(addprefix $(OBJ_DIR),$(SRC:%.c=%.o))

GREEN	:= \033[1;32m
NC		:= \033[0m

LIB 	:= make -sC mlx
LIB.A	:= mlx/libmlx_Linux.a


all: $(NAME)

$(NAME): $(OBJ)
	@$(LIB)
	@$(CC) $(OBJ) $(LIB.A) -lXext -lX11 -lm -lz -o $(NAME) && printf "$(GREEN)✔️ $(NAME)$(NC) compiled\n"

$(OBJ_DIR)%.o: %.c
	@mkdir -p  $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
