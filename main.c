/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:45 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/23 12:19:55 by avan-dam      ########   odam.nl         */
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
		return (ft_more_checks(line, mys));
	if (line[0] == ' ' || line[0] == '1' || line[0] == '2' || line[0] == '0')
		return (ft_find_map(line, mys));
	if ((ft_strcmp(line, "") == 0) && (mys->map == NULL))
		return (1);
	if ((ft_strcmp(line, "") == 0) && (mys->map != NULL))
		return (error_text(mys, "error in spacing elements in .cub file", 0));
	return (error_text(mys, "invalid element identifier", 0));
}

int		check_negatives(t_sto *mys)
{
	if ((mys->r[0] == 0) && (mys->f[0] == -1))
		return (error_text(mys, "Not all elements given", 0));
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
	if ((open(mys->no, O_RDONLY) == -1) || (open(mys->so, O_RDONLY) == -1)
	|| (open(mys->we, O_RDONLY) == -1) || (open(mys->ea, O_RDONLY) == -1))
		return (error_text(mys, "error opening texture", 0));
	if (open(mys->s, O_RDONLY) == -1)
		return (error_text(mys, "error in loading sprite", 0));
	if (mys->map == NULL)
		return (error_text(mys, "Map missing", 0));
	return (1);
}

int		ft_next_steps(t_sto *mys)
{
	if (check_negatives(mys) == -1)
		return (-1);
	if ((ft_split_cub3d(mys->map, '\n', mys)) == -1)
	{
		mys->error = "Problem with map";
		return (-1);
	}
	if ((ft_check_if_map_valid(mys)) == -1)
	{
		if (mys->error == NULL)
			mys->error = "map not valid";
		return (-1);
	}
	find_ceiling_floor_hx(mys);
	if (start_raycastin(mys) == -1)
	{
		if (mys->error == NULL)
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
		return (error_text(mys, "Error getting new line", 1));
	while (liney != 0)
	{
		if (liney == -1)
			return (error_text(mys, "Error getting new line", 1));
		if (check_liney(line, mys) == -1)
			return (free_storage(&line, mys));
		free(line);
		liney = get_next_line(fd, &line);
		if ((ft_strcmp(line, "") != 0) && (liney == 0))
		{
			if (check_liney(line, mys) == -1)
				return (error_text(mys, "Error getting new line", 1));
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
	char	*end;

	i = 0;
	ft_zero_struct(&mys);
	if ((argc == 3) && (ft_strcmp(argv[2], "--save") == 0))
		mys.save = 1;
	if ((argc != 2) && (mys.save == 0))
		return (error_text(&mys, "wrong number of arguments", 1));
	end = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strcmp(".cub", end) != 0)
		return (error_text(&mys, "not a .cub file", 1));
	free(end);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_text(&mys, "open failed", 1));
	if ((ft_find_info(&mys, fd)) == -1)
		return (ft_error(&mys));
	if (close(fd) == -1)
		return (error_text(&mys, "close failed", 1));
	return (1);
}
