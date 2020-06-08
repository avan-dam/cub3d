/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:45 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/08 18:09:40 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libgnl.h"

int		check_liney(char *line, t_sto *mys)
{
	int	i;

	i = 0;
	if (line[0] == 'R')
		return (fill_res(line, mys, 1, 0));
	if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O')
	|| (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' && line[1] == 'A'))
		return (fill_texture(line, mys));
	if (line[0] == 'S')
		return (sprite_path(line, mys));
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (((line[0] == 'F' && mys->f[0] != -1)) ||
		((line[0] == 'C' && mys->c[1] != -1)) || (mys->map != NULL)
		|| (mys->split != NULL))
			return (error_text(mys, "Error in order .cub file", 0));
		if (floor_ceiling_colour(line, mys, line[0], 0) != 3)
			return (-1);
		return (1);
	}
	if (line[0] == ' ' || line[0] == '1' || line[0] == '2' || line[0] == '0')
		return (ft_find_map(line, mys));
	if ((ft_strcmp(line, "") == 0) && (mys->map == NULL))
		return (1);
	return (-1);
}

int		check_negatives(t_sto *mys)
{
	if ((mys->r[0] <= 0) || (mys->r[1] <= 0))
		return (error_text(mys, "Error in resolution", 0));
	if ((mys->f[0] == -1) || (mys->f[1] == -1) || (mys->f[2] == -1))
		return (error_text(mys, "Error in floor colour", 0));
	if ((mys->c[0] == -1) || (mys->c[1] == -1) || (mys->c[2] == -1))
		return (error_text(mys, "Error in ceiling colour", 0));
	if ((mys->no == 0) || (mys->so == 0) || (mys->we == 0) ||
	(mys->ea == 0) || (mys->s == 0))
		return (error_text(mys, "Error in textures/sprite", 0));
	if ((mys->f[0] > 255) || (mys->f[1] > 255) || (mys->f[2] > 255))
		return (error_text(mys, "Error in floor colour", 0));
	if ((mys->c[0] > 255) || (mys->c[1] > 255) || (mys->c[2] > 255))
		return (error_text(mys, "Error in ceiling colour", 0));
	return (1);
}

int		ft_next_steps(t_sto *mys)
{
	if ((ft_split_cub3d(mys->map, '\n', mys)) == -1)
	{
		mys->error = "Failed to split map";
		return (-1);
	}
	if (check_negatives(mys) == -1)
		return (-1);
	if ((ft_check_if_map_valid(mys)) == -1)
	{
		mys->error = "map not valid";
		return (-1);
	}
	find_ceiling_floor_hx(mys);
	if (start_raycastin(mys) == -1)
	{
		mys->error = "error in raycasting";
		return (-1);
	}
	return (0);
}

int		ft_find_info(t_sto *mys, int fd)
{
	char	*line;
	int		liney;

	liney = get_next_line(fd, &line);
	if (liney == -1)
	{
		mys->error = "Failed to get next line";
		return (-1);
	}
	while (liney != 0)
	{
		if (liney == -1)
			return (free_storage(&line, mys));
		if (check_liney(line, mys) == -1)
			return (free_storage(&line, mys));
		free(line);
		liney = get_next_line(fd, &line);
		if ((ft_strcmp(line, "") != 0) && (liney == 0))
		{
			if (check_liney(line, mys) == -1)
				return (free_storage(&line, mys));
			free(line);
		}
	}
	return (ft_next_steps(mys));
}

int		main(int argc, char **argv)
{
	t_sto	mys;
	int		i;
	int		fd;

	i = 0;
	ft_zero_struct(&mys);
	// check this!! 
	if ((argc == 3) && (ft_strcmp(argv[2], "--save") == 0))
		mys.save = 1;
	if ((argc != 2) && (mys.save != 1))
		return (error_text(&mys, "wrong number of arguments", 1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		mys.error = "open failed";
		return (ft_error(&mys));
	}
	if ((ft_find_info(&mys, fd)) == -1)
		return (ft_error(&mys));
	if (close(fd) == -1)
	{
		mys.error = "close failed";
		return (ft_error(&mys));
	}
}
