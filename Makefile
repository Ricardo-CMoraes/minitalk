NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Ilibft -Iincludes

SRC_CLIENT = src/mandatory/client.c src/utils.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER = src/mandatory/server.c src/utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)

SRC_CLIENT_BONUS = src/bonus/client_bonus.c src/utils.c
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

SRC_SERVER_BONUS = src/bonus/server_bonus.c src/utils.c
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)
	$(CC) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)
	$(CC) $(OBJ_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
