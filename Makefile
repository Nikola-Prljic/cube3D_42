
NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC =	./cfiles/map_check/ft_getline/ft_getline_ultis.c \
		./cfiles/map_check/ft_getline/ft_getline.c \
		./cfiles/map_check/ft_getline/ft_strchr.c \
		./cfiles/map_check/ft_atoi.c \
		./cfiles/map_check/map_check_utils.c \
		./cfiles/map_check/map_check_walls.c \
		./cfiles/map_check/map_check.c \
		./cfiles/map_check/map_colors.c \
		./cfiles/map_check/map_surrounded_by_walls.c \
		./cfiles/map_check/map_textures.c \
		./cfiles/map_check/map_utils.c \
		./cfiles/convertions.c \
		./cfiles/input_handle.c \
		./cfiles/loadtextures.c \
		./cfiles/main.c \
		./cfiles/utils.c \
		./cfiles/window_draw.c \
		./cfiles/window_loop.c \
		./cfiles/player_action.c \
		./cfiles/wall_collision.c \
		./cfiles/raycasting/raycasting.c \
		./cfiles/raycasting/raylen.c \
		./cfiles/raycasting/raycasting_utils1.c\

all : $(NAME)

OBJ  =	$(SRC:.c=.o)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -lmlx -lXext -lX11 -lm -o $(NAME)	
	@echo "$(NAME) created"

clean :
	@rm -f $(OBJ)
	@echo "Done cleaning"

fclean : clean
	@rm -f cub3D
	@echo "Everything cleaned"

re : fclean all

.PHONY:	all clean fclean re
