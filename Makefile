NAME = so_long

SRC = srcs/main.c srcs/mlx.c srcs/error_handling.c \
	  srcs/check_map.c srcs/flood_fill.c \
	  srcs/keyboard.c srcs/moves.c \
	  srcs/render.c srcs/render2.c 
	  
CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3 -std=gnu17

INCLUDES = -Ilibft -Iincludes -Imlx

OBJECT_SRC =  $(SRC:.c=.o)

#big L is to specify where the compliler should look for libraries. small l is to link the specified library.
#lX11 is the graphical user interface library for X window system, Xext provides extensions for the X window system
$(NAME): $(OBJECT_SRC)
	@make -C libft all
	@make -C mlx all
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(OBJECT_SRC) mlx/libmlx_Linux.a libft/libft.a -lXext -lX11 -lz -lm -o $@

%.o : %.c 
	@$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	@make -C libft clean
	@make -C mlx clean
	@rm -rf $(OBJECT_SRC)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
