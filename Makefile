
NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = 	./cfiles/ft_split.c \
		./cfiles/ft_substr.c \
		./cfiles/main.c \
		./cfiles/input_handle.c \
		./cfiles/map_check.c \
		./cfiles/map_open.c \
		./cfiles/map_open_utils.c \
		./cfiles/utils.c \

all : $(NAME)

OBJ  =	$(SRC:.c=.o)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -lXext -lX11 -o $(NAME)
	@echo "$(NAME) created"

clean :
	@rm -f $(OBJ)
	@echo "Done cleaning"

fclean : clean
	@rm -f cub3D
	@echo "Everything cleaned"

re : fclean all

.PHONY:	all clean fclean re