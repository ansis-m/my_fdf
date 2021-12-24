SRC = main.c main_utils.c ft_atoi.c draw_map.c draw_map_utils.c draw_map_utils2.c get_next_line.c \
get_next_line_utils.c rotate.c draw_line.c draw_line_utils.c keycode_utils.c

INC=/usr/include
DIR=../minilibx-linux
INCLIB=$(INC)/../lib
CC = gcc

CFLAGS= -Wall -Wextra -Werror
LFLAGS = -L.. -L$(INCLIB) -lXext -lX11 -lm -lbsd

NAME= fdf

OBJ = $(SRC:%.c=%.o)
LIBRARY = $(DIR)/libmlx.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBRARY) fdf.h
	$(CC) -o $(NAME) $(OBJ) $(LIBRARY) $(LFLAGS)

clean:
	$(RM) $(OBJ) *~ core *.core

fclean:
	$(RM) $(NAME) $(OBJ) *~ core *.core

re:     fclean all

.PHONY:         all clean fclean re