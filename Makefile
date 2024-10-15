# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 20:13:46 by csweetin          #+#    #+#              #
#    Updated: 2024/10/11 17:53:50 by csweetin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

BUILD_DIR = build/
RAY_H = raycasting.h
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I $(MLX_DIR)
LIBS = -L $(MLX_DIR) -lmlx -L /usr/lib/X11 -lXext -lX11 -lm

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
CPPFLAGS:= $(INCLUDES) -MMD -MP

SRC = 	main.c \
		display.c \
		draw.c \
		events.c \
		utils.c \
		raycasting.c \
		#raycasting_2.c

OBJS = $(SRC:%.c=$(BUILD_DIR)%.o)
DEPS:= $(OBJS:%.o=%.d)

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(BUILD_DIR)%.o: %.c $(RAY_H)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 

$(MLX) :
	@make -C $(MLX_DIR) 2>/dev/null

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)
	@make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : fclean clean re all
