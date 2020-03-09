# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/09 11:50:01 by avan-dam       #+#    #+#                 #
#    Updated: 2020/03/09 16:21:07 by avan-dam      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = main.c

OFILES = $(SRCS:.c=.o)

INCLUDE = /Users/avan-dam/Documents/cub3d/libft/ /Users/avan-dam/Documents/cub3d/mlx/ /Users/avan-dam/Documents/cub3d/get_next_line/

all: $(OFILES) $(INCLUDES)
	make -C libft/
	cp libft/libft.a .
	make -C mlx/
	cp mlx/libmlx.dylib .
	make -C get_next_line/
	cp get_next_line/libgnl.a .
	$(CC) -Lmlx -lmlx -Llibft -lft -Lget_next_line -lgnl -framework OpenGL -framework AppKit -o $(NAME) $(OFILES)

%.o: %.c
	gcc -Ilibft -Imlx -c $< -o $@

clean:
	/bin/rm -f $(OFILES)
	make clean -C libft/
	make clean -C mlx/
	make clean -C get_next_line/

fclean: clean
	/bin/rm -f mlx/libmlx.dylib
	/bin/rm -f libmlx.dylib
	/bin/rm -f libft/libft.a
	/bin/rm -f libft.a
	/bin/rm -f get_nextline/libgnl.a
	/bin/rm -f libgnl.a
	/bin/rm -f $(NAME)

re: fclean all
