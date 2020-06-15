/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moving_more.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:53 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/12 00:44:05 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_move_right(t_master *big)
{
	if (big->move.move_right == 1)
	{
		if (big->ray.dir_x < 0.5 && big->ray.dir_x > -0.5)
		{
			if (big->mys.split[(int)(big->ray.pos_y)]
			[(int)(big->ray.pos_x - big->ray.dir_y * 0.1)] == '0')
			{
				big->move.counter++;
				big->ray.pos_x = big->ray.pos_x - big->ray.dir_y * 0.1;
				return (1);
			}
		}
		else
		{
			if (big->mys.split[(int)(big->ray.pos_y + big->ray.dir_x *
			0.1)][(int)(big->ray.pos_x)] == '0')
			{
				big->move.counter++;
				big->ray.pos_y = big->ray.pos_y + big->ray.dir_x * 0.1;
				return (1);
			}
		}
	}
	return (0);
}

int		ft_move_left(t_master *big)
{
	if (big->move.move_left == 1)
	{
		if (big->ray.dir_x < 0.5 && big->ray.dir_x > -0.5)
		{
			if (big->mys.split[(int)(big->ray.pos_y)]
			[(int)(big->ray.pos_x + big->ray.dir_y * 0.1)] == '0')
			{
				big->move.counter++;
				big->ray.pos_x = big->ray.pos_x + big->ray.dir_y * 0.1;
				return (1);
			}
		}
		else
		{
			if (big->mys.split[(int)(big->ray.pos_y - big->ray.dir_x *
			0.1)][(int)(big->ray.pos_x)] == '0')
			{
				big->move.counter++;
				big->ray.pos_y = big->ray.pos_y - big->ray.dir_x * 0.1;
				return (1);
			}
		}
	}
	return (0);
}

int		keypress(int keycode, t_master *big)
{
	if (keycode == 1)
		big->move.down = 1;
	if (keycode == 13)
		big->move.up = 1;
	if (keycode == 123)
		big->move.rotate_left = 1;
	if (keycode == 124)
		big->move.rotate_right = 1;
	if (keycode == 0)
		big->move.move_left = 1;
	if (keycode == 2)
		big->move.move_right = 1;
	if (keycode == 53)
		closeme(53, big);
	return (1);
}

int		keyrelease(int keycode, t_master *big)
{
	if (keycode == 1)
		big->move.down = 0;
	if (keycode == 13)
		big->move.up = 0;
	if (keycode == 123)
		big->move.rotate_left = 0;
	if (keycode == 124)
		big->move.rotate_right = 0;
	if (keycode == 0)
		big->move.move_left = 0;
	if (keycode == 2)
		big->move.move_right = 0;
	return (1);
}

int		keywhere(t_master *big)
{
	if ((ft_movedown(big) == 1) || (ft_moveup(big) == 1) ||
		(ft_rotate_left(big) == 1) || (ft_rotate_right(big) == 1)
		|| (ft_move_left(big) == 1) || (ft_move_right(big) == 1))
		ft_looping(big);
	return (1);
}
