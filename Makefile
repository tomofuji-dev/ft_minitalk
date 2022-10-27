SRCS = server.c client.c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = ./libft/
LIBFTNAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: libft server.o
	$(CC) $(CFLAGS) -o server server.o $(LIBFTNAME)

client: client.o
	$(CC) $(CFLAGS) -o client client.o $(LIBFTNAME)

libft: 
	make -C $(LIBFTDIR)
	mv $(LIBFTDIR)$(LIBFTNAME) ./

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make clean -C $(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	rm -f server client
	rm -f $(LIBFTNAME)

re: fclean all

.PHONY: all libft clean fclean re
