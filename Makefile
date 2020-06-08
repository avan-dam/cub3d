# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/09 11:50:01 by avan-dam      #+#    #+#                  #
#    Updated: 2020/06/08 17:01:55 by Amber         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = main.c ft_sort_my_map.c check_map_valid.c raycasting.c floor_ceiling.c \
		zero_structs.c zero_structs_more.c moving.c texture.c start_pos.c \
		sprite_me.c sprites_more.c raycasting_more.c ft_split_map.c cub_info.c \
		moving_more.c main_more.c error.c

OFILES = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDE = cub3d.h

all: $(NAME)

$(NAME): $(OFILES)
	make -C mlx/
	cp mlx/libmlx.dylib .
	make -C gnl/
	cp gnl/libgnl.a .
	$(CC) -Lmlx -lmlx -Lgnl -lgnl -framework OpenGL \
	-framework AppKit -o $(NAME) $(OFILES)

%.o: %.c $(INCLUDE)
	gcc -Imlx -Ignl $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OFILES)
	make clean -C mlx/
	make clean -C gnl/

fclean: clean
	/bin/rm -f mlx/libmlx.dylib
	/bin/rm -f libmlx.dylib
	/bin/rm -f gnl/libgnl.a
	/bin/rm -f libgnl.a
	/bin/rm -f $(NAME)

re: fclean all
