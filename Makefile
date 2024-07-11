CC = gcc
CFLAGS = -Wall -Werror -I.
LIB_SRCS = src/client.c \
		   src/connection.c \
		   src/data.c \
		   src/forest.c \
		   src/message.c \
		   src/response.c

LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_NAME = libforest.so

all: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(LIB_OBJS)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all
