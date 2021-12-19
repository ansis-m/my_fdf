SRC = main.c

INC=/usr/include
DIR=./minilibx-linux
INCLIB=$(INC)/../lib
CC = gcc

CFLAGS= -Wall -Wextra
LFLAGS = -L.. -L$(INCLIB) -lXext -lX11 -lm -lbsd

NAME= fdf

OBJ = $(SRC:%.c=%.o)
LIBRARY = $(DIR)/libmlx.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) -o $(NAME) $(OBJ) $(LIBRARY) $(LFLAGS)

$(LIBRARY):
	$(MAKE) -C ${DIR}

clean:
	$(RM) $(OBJ) *~ core *.core
	$(RM) ./minilibx-linux/obj

fclean:
	$(RM) $(NAME) $(OBJ) *~ core *.core
	$(MAKE) clean -C ${DIR}

re:     fclean all

.PHONY:         all clean fclean re