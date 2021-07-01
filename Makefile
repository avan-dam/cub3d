# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/09 11:50:01 by avan-dam      #+#    #+#                  #
#    Updated: 2021/07/01 10:46:26 by ambervandam   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	srcs/main.c \
		srcs/ft_sort_my_map.c \
		srcs/check_map_valid.c \
		srcs/raycasting.c \
		srcs/floor_ceiling.c \
		srcs/zero_structs.c \
		srcs/zero_structs_more.c \
		srcs/moving.c \
		srcs/texture.c \
		srcs/start_pos.c \
		srcs/sprite_me.c \
		srcs/sprites_more.c \
		srcs/raycasting_more.c \
		srcs/ft_split_map.c \
		srcs/cub_info.c \
		srcs/moving_more.c \
		srcs/main_more.c \
		srcs/error.c \
		srcs/save_bp.c \
		srcs/more_map_valid.c

OFILES = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O3 

INCLUDE = srcs/cub3d.h

all: $(NAME)

$(NAME): $(OFILES)
	make -C mlx/
	cp mlx/libmlx.dylib .
	make -C gnl/
	cp gnl/libgnl.a .
	gcc -Lmlx -lmlx -Lgnl -lgnl -framework OpenGL \
	-framework AppKit -o $(NAME) $(OFILES) $(FLAGS)

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

.PHONY: all clean fclean re
