/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moving.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:53 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/20 16:22:50 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

/*
** [both camera direction and camera plane must be rotated]
*/

int		ft_rotate_left(t_master *big)
{
	float	rot_speed;
	float	old_dir_x;
	float	old_plane_x;

	rot_speed = 0.1;
	old_dir_x = big->ray.dir_x;
	old_plane_x = big->ray.plane_x;
	if (big->move.rotate_left == 1)
	{
		big->move.counter++;
		big->ray.dir_x = big->ray.dir_x * cos(-rot_speed) -
		big->ray.dir_y * sin(-rot_speed);
		big->ray.dir_y = old_dir_x * sin(-rot_speed) +
		big->ray.dir_y * cos(-rot_speed);
		big->ray.plane_x = big->ray.plane_x * cos(-rot_speed) -
		big->ray.plane_y * sin(-rot_speed);
		big->ray.plane_y = old_plane_x * sin(-rot_speed) +
		big->ray.plane_y * cos(-rot_speed);
		return (1);
	}
	return (0);
}

int		ft_rotate_right(t_master *big)
{
	float rot_speed;
	float old_dir_x;
	float old_plane_x;

	rot_speed = 0.1;
	old_dir_x = big->ray.dir_x;
	old_plane_x = big->ray.plane_x;
	if (big->move.rotate_right == 1)
	{
		big->move.counter++;
		big->ray.dir_x = big->ray.dir_x *
		cos(rot_speed) - big->ray.dir_y * sin(rot_speed);
		big->ray.dir_y = old_dir_x * sin(rot_speed)
		+ big->ray.dir_y * cos(rot_speed);
		big->ray.plane_x = big->ray.plane_x * cos(rot_speed)
		- big->ray.plane_y * sin(rot_speed);
		big->ray.plane_y = old_plane_x * sin(rot_speed)
		+ big->ray.plane_y * cos(rot_speed);
		return (1);
	}
	return (0);
}

int		ft_moveup(t_master *big)
{
	float	move_speed;

	move_speed = 0.1;
	if (big->move.up == 1)
	{
		if (big->mys.split[(int)(big->ray.pos_y + (big->ray.dir_y * 5)
		* move_speed)][(int)(big->ray.pos_x + (big->ray.dir_x * 5)
		* move_speed)] == '0')
		{
			big->move.counter++;
			big->ray.pos_x = big->ray.pos_x + big->ray.dir_x * move_speed;
			big->ray.pos_y = big->ray.pos_y + big->ray.dir_y * move_speed;
			return (1);
		}
	}
	return (0);
}

int		ft_movedown(t_master *big)
{
	float move_speed;

	move_speed = 0.1;
	if (big->move.down == 1)
	{
		if (big->mys.split[(int)(big->ray.pos_y - (big->ray.dir_y * 5)
		* move_speed)][(int)(big->ray.pos_x - (big->ray.dir_x * 5)
		* move_speed)] == '0')
		{
			big->move.counter++;
			big->ray.pos_x = big->ray.pos_x - big->ray.dir_x * move_speed;
			big->ray.pos_y = big->ray.pos_y - big->ray.dir_y * move_speed;
			return (1);
		}
	}
	return (0);
}
