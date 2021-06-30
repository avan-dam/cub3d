/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_valid.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:19 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/20 15:37:13 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_floodfill(t_sto *mys, int x, int y)
{
	if (x < mys->row && x >= 0 && y >= 0)
	{
		if (mys->copy[x][y] == '1')
			return ;
		if (mys->copy[x][y] != '\0')
		{
			if (mys->copy[x][y] == '0' || mys->copy[x][y] == '2')
			{
				mys->copy[x][y] = 'Z';
				ft_floodfill(mys, x + 1, y);
				ft_floodfill(mys, x + 1, y + 1);
				ft_floodfill(mys, x, y + 1);
				ft_floodfill(mys, x + 1, y - 1);
				ft_floodfill(mys, x - 1, y);
				ft_floodfill(mys, x - 1, y + 1);
				ft_floodfill(mys, x, y - 1);
				ft_floodfill(mys, x - 1, y - 1);
			}
		}
	}
}

int		start_char(t_sto *mys, int x, int y, int p)
{
	while (x < mys->row)
	{
		while (mys->copy[x][y] != '\0')
		{
			if (mys->copy[x][y] == 'N' || (mys->copy[x][y] == 'S') ||
			(mys->copy[x][y] == 'E') || (mys->copy[x][y] == 'W'))
			{
				mys->copy[x][y] = 'Z';
				p++;
				if (x == mys->row - 1)
					return (-2);
				if ((x == 0) || (y == 0) || (x == mys->row - 1))
					return (-1);
				ft_floodfill(mys, x - 1, y);
				ft_floodfill(mys, x, y - 1);
				if (y != ft_strlen(mys->copy[x]))
					ft_floodfill(mys, x, y + 1);
				ft_floodfill(mys, x + 1, y);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (p);
}

int		ft_more_map_valid(char **copy, int x, int y)
{
	if (copy[x][y] == 'Z')
	{
		if ((x == 0) || (y == 0))
			return (-1);
		if ((copy[x][y + 1] == 'Z' || copy[x][y + 1] == '1') &&
		(copy[x][y - 1] == 'Z' || copy[x][y - 1] == '1') &&
		(copy[x + 1][y] == 'Z' || copy[x + 1][y] == '1') &&
		(copy[x - 1][y] == 'Z' || copy[x - 1][y] == '1') &&
		(copy[x - 1][y - 1] == 'Z' || copy[x - 1][y - 1] == '1') &&
		(copy[x + 1][y + 1] == 'Z' || copy[x + 1][y + 1] == '1') &&
		(copy[x + 1][y - 1] == 'Z' || copy[x + 1][y - 1] == '1') &&
		(copy[x - 1][y + 1] == 'Z' || copy[x - 1][y + 1] == '1'))
			return (1);
		return (-1);
	}
	return (1);
}

int		ft_check_lines(t_sto *mys, int x, int y)
{
	while (x < mys->row)
	{
		while (mys->copy[x][y] != '\0')
		{
			if (ft_more_map_valid(mys->copy, x, y) == -1)
				return (-1);
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int		ft_check_if_map_valid(t_sto *mys)
{
	int	x;
	int p;

	x = 0;
	if (ft_duplicate_map(mys) == -1)
		return (ft_free_copy(mys, -1));
	p = start_char(mys, 0, 0, -1);
	if (p == -1)
	{
		mys->error = "no starting character";
		return (ft_free_copy(mys, -1));
	}
	if (p == -2)
	{
		mys->error = "Invalid map";
		return (ft_free_copy(mys, -1));
	}
	if (p > 0)
	{
		mys->error = "More than one starting character in map";
		return (ft_free_copy(mys, -1));
	}
	if (ft_check_lines(mys, 0, 0) == -1)
		return (ft_free_copy(mys, -1));
	return (ft_free_copy(mys, 1));
}
