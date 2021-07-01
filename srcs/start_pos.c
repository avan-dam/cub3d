/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_pos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:59 by Amber         #+#    #+#                 */
/*   Updated: 2021/07/01 10:10:07 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_fill_plane(t_master *big)
{
	if ((big->ray.dir_x == 0) && (big->ray.dir_y == -1))
	{
		big->ray.plane_x = 0.66;
		big->ray.plane_y = 0;
	}
	if ((big->ray.dir_x == 0) && (big->ray.dir_y == 1))
	{
		big->ray.plane_x = -0.66;
		big->ray.plane_y = 0;
	}
	if ((big->ray.dir_x == 1) && (big->ray.dir_y == 0))
	{
		big->ray.plane_x = 0;
		big->ray.plane_y = 0.66;
	}
	if ((big->ray.dir_x == -1) && (big->ray.dir_y == 0))
	{
		big->ray.plane_x = 0;
		big->ray.plane_y = -0.66;
	}
}

void	ft_fill_ray(t_master *big, int x, int y)
{
	if (big->mys.split[y][x] == 'N')
	{
		big->ray.dir_x = 0;
		big->ray.dir_y = -1;
	}
	if (big->mys.split[y][x] == 'S')
	{
		big->ray.dir_x = 0;
		big->ray.dir_y = 1;
	}
	if (big->mys.split[y][x] == 'E')
	{
		big->ray.dir_x = 1;
		big->ray.dir_y = 0;
	}
	if (big->mys.split[y][x] == 'W')
	{
		big->ray.dir_x = -1;
		big->ray.dir_y = 0;
	}
	big->mys.split[y][x] = '0';
	ft_fill_plane(big);
}

int		start_pos(t_master *big, int y, int x)
{
	ft_numb_sprites(big);
	big->ray.w = big->mys.r[0];
	while (big->mys.split[y][x] != '\0')
	{
		while (big->mys.split[y][x] != '\0')
		{
			if ((big->mys.split[y][x] == 'N' || big->mys.split[y][x] == 'S'
			|| big->mys.split[y][x] == 'E' || big->mys.split[y][x] == 'W'))
			{
				if (big->ray.pos_x != 0)
					return (-1);
				big->ray.pos_x = x + 0.5;
				big->ray.pos_y = y + 0.5;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (big->ray.pos_x == 0)
		return (-1);
	ft_fill_ray(big, big->ray.pos_x - 0.5, big->ray.pos_y - 0.5);
	return (1);
}

/*
** [map_x = which box of the map we're in]
** [deltadist = length of ray from one x or y-side to next x or y-side]
*/

void	ft_find_variables(t_master *big, int x)
{
	big->ray.camera_x = 2 * (x / big->ray.w) - 1;
	big->ray.ray_dir_y = big->ray.dir_y + big->ray.plane_y * big->ray.camera_x;
	big->ray.ray_dir_x = big->ray.dir_x + big->ray.plane_x * big->ray.camera_x;
	big->ray.map_x = (int)big->ray.pos_x;
	big->ray.map_y = (int)big->ray.pos_y;
	big->ray.deltadist_x = fabs(1 / big->ray.ray_dir_x);
	big->ray.deltadist_y = fabs(1 / big->ray.ray_dir_y);
}
