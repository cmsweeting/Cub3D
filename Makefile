# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 11:01:27 by cdomet-d          #+#    #+#              #
#    Updated: 2024/10/21 17:19:33 by cdomet-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

BDIR := .bdir/

LFTDIR := libs/libft
MLXDIR := libs/mlx
SDIR:= src/

MLX = $(MLXDIR)/libmlx_Linux.a
LIB := $(LFTDIR)/libft.a

H:= -I src/includes/ -I libs/libft -I libs/mlx

CC := cc
CFLAGS := -Werror -Wextra -Wall -Wshadow #-fsanitize=address -fno-omit-frame-pointer
#-g3 
# -Ofast
CPPFLAGS = -MMD -MP $(H)
MAKEFLAGS += --no-print-directory
MFLAGS = -L$(MLXDIR) -lmlx_Linux -L/usr/lib -I $(MLX) -lX11 -lm -lz -lXext $(MLX)

SRC +=	main.c \
		print_strcts.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ PARSING ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC += $(addprefix $(MADIR), $(MASRC))
MADIR:=	parsing/memory_allocation/
MASRC:=	memalloc.c \
		destroy_structs.c \

SRC += $(addprefix $(PDIR), $(PSRC))
PDIR:=	parsing/
PSRC:=	extract_file.c \
		get_map_data.c \
		handle_colors.c \
		init_mlx.c \
		init_textures.c \
		is_map_valid.c \
		iterative_floodfill.c \
		p_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ ERRORS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC += $(addprefix $(RAYDIR), $(RAYSRC))
RAYDIR:=	error_handling/
RAYSRC:=	error_handling.c \
		
# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ RAYCASTING ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC += $(addprefix $(MINIDIR), $(MINISRC))
MINIDIR:=	raycasting/minimap/
MINISRC:=	minimap.c \

SRC += $(addprefix $(EDIR), $(ESRC))
EDIR:=	raycasting/
ESRC:=	display.c \
		draw.c \
		events.c \
		raycasting.c \
		utils.c \

$(BDIR)%.o: $(SDIR)%.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

OBJS := $(addprefix $(BDIR), $(SRC:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)
RM := rm -rf

all: $(NAME)

$(NAME): $(LIB) $(MLX) $(OBJS)
	@printf '$(B)\n%.40s\n$(R)' "-- Making $(NAME)... ------------------------------------------------------------------"
	$(CC) $(CFLAGS) $(OBJS) -L $(LFTDIR) $(MFLAGS) -o $(NAME) -lft
	@printf '$(B)%.40s\n\n$(R)' "-- $(NAME) done ! ---------------------------------------------------------------------"

$(LIB): FORCE
	@echo "$(FAINT)"
	make -C $(LFTDIR)
	@echo "$(RESET)"

$(MLX): FORCE
	@echo "$(FAINT)"
	make -C $(MLXDIR)
	@echo "$(RESET)"

 -include $(DEPS)

clean:
	@printf '$(B)%.40s\n\n$(R)' "-- $(NAME) cleaned up ! --------------------------------------------------------------"
	$(RM) $(BDIR)
	make -C $(LFTDIR) $@
	make -C $(MLXDIR) $@

fclean: clean
	$(RM) $(MLX)
	make -C $(LFTDIR) $@
	$(RM) $(NAME)
	@echo

print:
	@echo $(H)

cdir:= $(shell pwd)
val:= valgrind --track-fds=yes --log-file="$(cdir)/val.log" --leak-check=full --show-leak-kinds=all --track-origins=yes
run: all
	$(val) ./$(NAME) maps/map1.cub

re: fclean all
# Formatting combinations
# Text
# reset
R=\033[0m
# faint
F=\033[2m
# underlined
U=\033[4m
# bold
BO=\033[1m

# Font color
# red
RE=\033[0;31m 
# green
G=\033[0;32m
# yellow
Y=\033[0;33m
# blue
B=\033[0;34m
# magenta
M=\033[0;35m
# cyan
C=\033[0;36m
# white
W=\033[0;37m
# pink
P=\033[38;5;206m.

# Background
BG_RED=\033[41m
BG_GREEN=\033[42m
BG_YELLOW=\033[43m
BG_B=\033[44m
BG_MAGENTA=\033[45m
BG_C=\033[46m
BG_WHITE=\033[47m

FORCE : 
.PHONY : clean fclean all re run help kitty display force bonus