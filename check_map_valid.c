/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_valid.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:00:19 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/08 17:54:55 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_floodfill(t_sto *mys, int x, int y)
{
	if (x < mys->row && x >= 0 && y >= 0)
	{
		if (mys->split[x][y] != '\0')
		{
			if (mys->split[x][y] == '1')
				return ;
			if (mys->split[x][y] == '0')
			{
				mys->split[x][y] = 'Z';
				ft_floodfill(mys, x + 1, y);
				ft_floodfill(mys, x, y + 1);
				ft_floodfill(mys, x - 1, y);
				ft_floodfill(mys, x, y - 1);
			}
		}
	}
}

int		ft_find_first_zero(t_sto *mys)
{
	int	x;
	int	y;
	int p;

	x = 1;
	y = 0;
	p = -1;
	while (x < mys->row)
	{
		while (mys->split[x][y] != '\0')
		{
			if (mys->split[x][y] == 'N' || (mys->split[x][y] != 'S') ||
			(mys->split[x][y] != 'E') || (mys->split[x][y] != 'W'))
			{
				p = 1;
				ft_floodfill(mys, x, y);
			}
			y++;
		}
		y = 0;
		x++;
	}
	if (p == -1)
		return (-1);
	return (1);
}

int		ft_more_map_valid(char **split, int x, int y)
{
	if (split[x][0] == 'Z' || split[x][0] == 'N' || split[x][0] == 'S'
	|| split[x][0] == 'E' || split[x][0] == 'W' || split[x][0] == '2')
		return (-1);
	if (split[x][y] == ' ' && (split[x][y + 1] == 'Z' ||
	split[x][y + 1] == '2' || split[x][y + 1] == 'N' ||
	split[x][y + 1] == 'E' || split[x][y + 1] == 'S' || split[x][y + 1] == 'W'))
		return (-1);
	if ((split[x][y] == 'Z' || split[x][y] == '2' || split[x][y] == 'N'
	|| split[x][y] == 'E' || split[x][y] == 'S' || split[x][y] == 'W')
	&& (split[x][y + 1] == ' ' || split[x][y + 1] == '\0'))
		return (-1);
	if ((split[x][y] == 'Z' || split[x][y] == '2' || split[x][y] == 'N'
	|| split[x][y] == 'E' || split[x][y] == 'S' || split[x][y] == 'W')
	&& split[x + 1][y] == ' ')
		return (-1);
	if ((split[x][y] == 'Z' && !(split[x - 1][y])) ||
	(split[x][y] == 'Z' && !(split[x + 1][y])))
		return (-1);
	if (split[x][y] == ' ' && (split[x + 1][y] == 'Z' ||
	split[x + 1][y] == '2' || split[x + 1][y] == 'N' || split[x + 1][y] == 'E'
	|| split[x + 1][y] == 'S' || split[x + 1][y] == 'W'))
		return (-1);
	if (split[x][y] == '2' && !(split[x - 1][y]))
		return (-1);
	return (1);
}

int		ft_check_lines(t_sto *mys, int x, int y)
{
	while (x < mys->row - 1)
	{
		while (mys->split[x][y] != '\0')
		{
			if ((ft_more_map_valid(mys->split, x, y) == -1) ||
			(mys->split[x][y] == '2' && !(mys->split[x + 1][y])) ||
			(mys->split[x][y] == '2' && (mys->split[x][y + 1] == ' ')))
				return (-1);
			y++;
		}
		y = 0;
		x++;
	}
	while (mys->split[x][y] != '\0')
	{
		if ((mys->split[x][y] == '2') || (mys->split[x][y] == 'Z'))
			return (-1);
		y++;
	}
	return (1);
}

int		ft_check_if_map_valid(t_sto *mys)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (ft_find_first_zero(mys) == -1)
		return (-1);
	if ((ft_check_lines(mys, 0, 0)) == -1)
		return (error_text(mys, "Map not valid", 0));
	while (x < mys->row)
	{
		while (mys->split[x][y] != '\0')
		{
			if (mys->split[x][y] == 'Z')
				mys->split[x][y] = '0';
			y++;
		}
		x++;
		y = 0;
	}
	return (1);
}
