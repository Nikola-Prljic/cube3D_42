
NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = 	input_handle.c \
		main.c \
		map_check.c \
		utils.c \

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