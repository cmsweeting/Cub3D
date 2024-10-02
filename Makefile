#HEADER

NAME = cub

BUILD_DIR = build/
RAY_H = raycasting.h
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I $(MLX_DIR)
LIBS = -L $(MLX_DIR) -lmlx -L /usr/lib/X11 -lXext -lX11 -lm

CC = cc
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS:= $(INCLUDES) -MMD -MP

SRC = 	main.c \
		display.c \
		raycasting.c \
		draw.c \

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
