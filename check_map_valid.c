/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_valid.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:19 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/12 20:22:50 by Amber         ########   odam.nl         */
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
				ft_floodfill(mys, x, y + 1);
				ft_floodfill(mys, x - 1, y);
				ft_floodfill(mys, x, y - 1);
			}
		}
	}
}

int		start_char(t_sto *mys, int i, int x, int y)
{
	int p;

	p = -1;
	while (x < mys->row)
	{
		while (mys->copy[x][y] != '\0')
		{
			if (mys->copy[x][y] == 'N' || (mys->copy[x][y] == 'S') ||
			(mys->copy[x][y] == 'E') || (mys->copy[x][y] == 'W'))
			{
				mys->copy[x][y] = 'Z';
				p = 1;
				if ((x == 0) || (y == 0) || (x == mys->row - 1))
					return (-1);
				if (i == 0)
				{
					ft_floodfill(mys, x - 1, y);
					ft_floodfill(mys, x, y - 1);
					if (y != ft_strlen(mys->copy[x]))
						ft_floodfill(mys, x, y + 1);
					if (x != mys->row - 1)
						ft_floodfill(mys, x + 1, y);
				}
				if (i == 1)
					if ((ft_check_lines(mys, x, y)) == -1)
						return (error_text(mys, "Map not valid", 0));
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
		if ((copy[x][y + 1] == 'Z' || copy[x][y + 1] == '1') &&
		(copy[x][y - 1] == 'Z' || copy[x][y - 1] == '1') &&
		(copy[x + 1][y] == 'Z' || copy[x + 1][y] == '1') &&
		(copy[x - 1][y] == 'Z' || copy[x - 1][y] == '1'))
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

int		ft_duplicate_map(t_sto *mys)
{
	int i;
	int j;
	int length;

	i = 0;
	j = 0;
	mys->copy = (char**)malloc(sizeof(char*) * (mys->row + 1));
	if (mys->copy == NULL)
		return (-1);
	while (i < mys->row)
	{
		length = ft_strlen(mys->split[i]);
		mys->copy[i] = (char *)malloc(sizeof(char) * (length + 1));
		while (j < ft_strlen(mys->split[i]))
		{
			mys->copy[i][j] = mys->split[i][j];
			j++;
		}
		mys->copy[i][j] = '\0';
		j = 0;
		i++;
	}
	mys->copy[mys->row] = NULL;
	return (1);
}

int		ft_free_copy(t_sto *mys, int i)
{
	int x;

	x = 0;
	while (x < mys->row)
	{
		if (mys->copy[x])
		{
			free(*mys->copy);
			*mys->copy = 0;
		}
		x++;
	}
	return (i);
}

int		ft_check_if_map_valid(t_sto *mys)
{
	int	x;

	x = 0;
	if (ft_duplicate_map(mys) == -1)
		return (ft_free_copy(mys, -1));
	if (start_char(mys, 0, 0, 0) == -1)
		return (ft_free_copy(mys, -1));
	if (ft_check_lines(mys, 0, 0) == -1)
		return (ft_free_copy(mys, -1));
	return (ft_free_copy(mys, 1));
}
