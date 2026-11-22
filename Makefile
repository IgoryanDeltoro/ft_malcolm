NAME = ft_malcolm
CFLAGS = -Wall -Wextra -Werror
CC = cc -g
RM = rm -rf

SRC =  	main.c \
		utils.c \
		args.c \
		arp.c \
		net.c \
		signals.c \
		utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

