SERVER = server
CLIENT  = client
SRCS = $(SERVER).c $(CLIENT).c
OBJS = $(SRCS:.c=.o)
LIBFTDIR = libft/
LIBFTNAME = libft.a
LIBFT = $(LIBFTDIR)$(LIBFTNAME)
# NAME = out

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

# $(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(LIBFTNAME) server.o
	$(CC) $(CFLAGS) -o $(SERVER) server.o $(LIBFTNAME)

$(CLIENT): $(LIBFTNAME) client.o
	$(CC) $(CFLAGS) -o $(CLIENT) client.o $(LIBFTNAME)

$(LIBFTNAME): 
	make -C $(LIBFTDIR)
	cp $(LIBFT) ./

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make clean -C $(LIBFTDIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(LIBFTNAME)
	rm -f $(SERVER) $(CLIENT)

re:
 	make -C . fclean
  	make -C . all

.PHONY: all clean fclean re
