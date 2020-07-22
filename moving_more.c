/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moving_more.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:53 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 15:03:33 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_move_right(t_master *big)
{
	float	move_speed;

	move_speed = 0.1;
	if (big->move.move_right == 1)
	{
		if (big->mys.split[(int)(big->ray.pos_y + (big->ray.plane_y * 5)
		* move_speed)][(int)(big->ray.pos_x + (big->ray.plane_x * 5)
		* move_speed)] == '0')
		{
			big->move.counter++;
			big->ray.pos_x = big->ray.pos_x + big->ray.plane_x * move_speed;
			big->ray.pos_y = big->ray.pos_y + big->ray.plane_y * move_speed;
			return (1);
		}
	}
	return (0);
}

int		ft_move_left(t_master *big)
{
	float	move_speed;

	move_speed = 0.1;
	if (big->move.move_left == 1)
	{
		if (big->mys.split[(int)(big->ray.pos_y - (big->ray.plane_y * 5)
		* move_speed)][(int)(big->ray.pos_x - (big->ray.plane_x * 5)
		* move_speed)] == '0')
		{
			big->move.counter++;
			big->ray.pos_x = big->ray.pos_x - big->ray.plane_x * move_speed;
			big->ray.pos_y = big->ray.pos_y - big->ray.plane_y * move_speed;
			return (1);
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
