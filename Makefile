# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 18:10:28 by tbraud            #+#    #+#              #
#    Updated: 2025/01/21 00:05:00 by brguicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
NAME_BONUS := cub3D_bonus

SRC_DIR	:= src/
OBJ_DIR	:= obj/

OBJ_DIR_BONUS	:= obj_bonus/

CC		:= gcc
CFLAGS	:= -Wextra -Wall -Werror -g

INCLUDE	:= -I ./include

SRC		:=	src/main.c \
			src/init.c \
			src/error/ft_error.c \
			src/error/parsing_error.c \
			src/player/ft_direction.c \
			src/player/ft_move.c \
			src/player/ft_position.c \
			src/render/ft_display.c \
			src/render/ft_raycasting_utils.c \
			src/render/ft_raycasting.c \
			src/render/put_pixel.c \
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

SRC_BONUS	:=	bonus/main_bonus.c \
			bonus/init_bonus.c \
			bonus/error/ft_error_bonus.c \
			bonus/error/parsing_error_bonus.c \
			bonus/player/ft_direction_bonus.c \
			bonus/player/ft_mouse_bonus.c \
			bonus/player/ft_display_bonus.c \
			bonus/player/ft_move_bonus.c \
			bonus/player/ft_position_bonus.c \
			bonus/player/ft_raycasting_bonus.c \
			bonus/player/put_pixel_bonus.c \
			bonus/parsing/ft_parse_bonus.c \
			bonus/parsing/ft_get_colors_bonus.c \
			bonus/parsing/ft_get_texture_path_bonus.c \
			bonus/parsing/ft_verif_map_bonus.c \
			bonus/parsing/verif_map_utils_bonus.c \
			bonus/utils/ft_split_bonus.c \
			bonus/utils/ft_utils_bonus.c \
			bonus/utils/get_next_line_utils_bonus.c \
			bonus/utils/get_next_line_bonus.c \
			bonus/utils/ft_putstr_fd_bonus.c \
			bonus/utils/len_bonus.c \
			bonus/utils/alloc_bonus.c \
			bonus/utils/free_bonus.c


OBJ		:= $(addprefix $(OBJ_DIR),$(SRC:%.c=%.o))
OBJ_BONUS := $(addprefix $(OBJ_DIR_BONUS),$(SRC_BONUS:%.c=%.o))

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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	@$(LIB)
	@$(CC) $(OBJ_BONUS) $(LIB.A) -lXext -lX11 -lm -lz -o $(NAME_BONUS) && printf "$(GREEN)✔️ $(NAME_BONUS)$(NC) compiled\n"

$(OBJ_DIR_BONUS)%.o: %.c
	@mkdir -p  $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: clean all

.PHONY: all clean fclean re
