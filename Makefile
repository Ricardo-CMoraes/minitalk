NAME_CLIENT = client
NAME_SERVER = server

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Ilibft -Iincludes

SRC_CLIENT = src/mandatory/client.c src/utils.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER = src/mandatory/server.c src/utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test
