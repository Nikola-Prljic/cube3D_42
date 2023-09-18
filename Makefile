
NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

INLCUDES = ./includes/cub3d.h
INLCUDES_BONUS = ./includes/cub3d_bonus.h
INLCUDES_DEFINES = ./includes/cub3d_defines.h

SRC =	./cfiles/map_check/ft_getline/ft_getline_ultis.c\
		./cfiles/map_check/ft_getline/ft_getline.c \
		./cfiles/map_check/ft_getline/ft_strchr.c \
		./cfiles/map_check/ft_atoi.c \
		./cfiles/map_check/ft_matrix_push_back.c \
		./cfiles/map_check/ft_split.c \
		./cfiles/map_check/map_check_utils.c \
		./cfiles/map_check/map_check_walls.c \
		./cfiles/map_check/map_check.c \
		./cfiles/map_check/map_colors.c \
		./cfiles/map_check/map_colors_utils.c \
		./cfiles/map_check/map_surrounded_by_walls.c \
		./cfiles/map_check/map_textures.c \
		./cfiles/map_check/map_utils.c \
		./cfiles/convertions.c \
		./cfiles/free_data.c \
		./cfiles/input_handle.c \
		./cfiles/loadtextures.c \
		./cfiles/main.c \
		./cfiles/utils.c \
		./cfiles/window_draw.c \
		./cfiles/window_loop.c \
		./cfiles/player_action.c \
		./cfiles/raycasting/raycasting.c \
		./cfiles/raycasting/raylen.c \
		./cfiles/raycasting/raycasting_utils1.c\


SRC_BONUS =	./cfiles/map_check/ft_getline/ft_getline_ultis.c\
		./cfiles/map_check/ft_getline/ft_getline.c \
		./cfiles/map_check/ft_getline/ft_strchr.c \
		./cfiles/map_check/ft_atoi.c \
		./cfiles/map_check/ft_matrix_push_back.c \
		./cfiles/map_check/ft_split.c \
		./cfiles/map_check/map_check_utils.c \
		./cfiles/map_check/map_check_walls.c \
		./cfiles/map_check/map_check.c \
		./cfiles/map_check/map_colors.c \
		./cfiles/map_check/map_colors_utils.c \
		./cfiles/map_check/map_surrounded_by_walls.c \
		./cfiles/map_check/map_textures.c \
		./cfiles/map_check/map_utils.c \
		./cfiles/convertions.c \
		./cfiles/free_data.c \
		./cfiles/input_handle.c \
		./cfiles/loadtextures.c \
		./cfiles/main.c \
		./cfiles/utils.c \
		./cfiles/window_draw.c \
		./cfiles/window_loop.c \
		./cfiles/raycasting/raycasting.c \
		./cfiles/raycasting/raylen.c \
		./cfiles/raycasting/raycasting_utils1.c\
		./bonus/player_action_bonus.c \
		./bonus/wall_collision_bonus.c \

all : $(NAME)

OBJ  =	$(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(OBJ) : $(INLCUDES) $(INLCUDES_DEFINES)
$(OBJ_BONUS) : $(INLCUDES_BONUS) $(INLCUDES_DEFINES)

./cfiles/map_check/ft_getline/ft_getline_ultis.o : ./cfiles/map_check/ft_getline/ft_getline.h
./cfiles/map_check/ft_getline/ft_getline.o : ./cfiles/map_check/ft_getline/ft_getline.h
./cfiles/map_check/ft_getline/ft_strchr.o  : ./cfiles/map_check/ft_getline/ft_getline.h

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(NAME) created"

bonus : $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(CFLAGS) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(NAME) with bonus created"

debug : CFLAGS += -g
debug : re

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@echo "Done cleaning"

fclean : clean
	@rm -f cub3D
	@echo "Everything cleaned"

re : fclean all

.PHONY:	all clean fclean re
