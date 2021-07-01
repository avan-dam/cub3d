/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:59:46 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:07:13 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

/*
** [jump to next map square, OR in x-direction, OR in y-direction]
*/

void	ft_dda(t_master *big)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (big->ray.sidedist_x < big->ray.sidedist_y)
		{
			big->ray.sidedist_x = big->ray.sidedist_x + big->ray.deltadist_x;
			big->ray.map_x = big->ray.map_x + big->ray.step_x;
			big->ray.side = 0;
		}
		else
		{
			big->ray.sidedist_y = big->ray.sidedist_y + big->ray.deltadist_y;
			big->ray.map_y = big->ray.map_y + big->ray.step_y;
			big->ray.side = 1;
		}
		if (big->mys.split[(int)big->ray.map_y][(int)big->ray.map_x] == '1')
			hit = 1;
	}
}

/*
** [calculate step and initial sideDist]
** [deltadist = length of ray from one x or y-side to next x or y-side]
** [side dist = length of ray from current position to next x or y-side]
*/

void	ft_find_sidedist(t_master *big)
{
	if (big->ray.ray_dir_x < 0)
	{
		big->ray.step_x = -1;
		big->ray.sidedist_x =
		(big->ray.pos_x - big->ray.map_x) * big->ray.deltadist_x;
	}
	else
	{
		big->ray.step_x = 1;
		big->ray.sidedist_x =
		(big->ray.map_x + 1.0 - big->ray.pos_x) * big->ray.deltadist_x;
	}
	if (big->ray.ray_dir_y < 0)
	{
		big->ray.step_y = -1;
		big->ray.sidedist_y =
		(big->ray.pos_y - big->ray.map_y) * big->ray.deltadist_y;
	}
	else
	{
		big->ray.step_y = 1;
		big->ray.sidedist_y =
		(big->ray.map_y + 1.0 - big->ray.pos_y) * big->ray.deltadist_y;
	}
}

/*
** [line_height = Calculate height of line to draw on screen]
** [then calculate lowest and highest pixel to fill in current stripe]
*/

void	ft_wall_height(t_master *big, int x)
{
	int		draw_end;
	int		draw_start;
	char	*dst;

	dst = NULL;
	if (big->ray.side == 0)
		big->ray.perpwalldist = ((big->ray.map_x - big->ray.pos_x +
		(1 - big->ray.step_x) / 2)) / big->ray.ray_dir_x;
	else
		big->ray.perpwalldist = (big->ray.map_y - big->ray.pos_y +
		(1 - big->ray.step_y) / 2) / big->ray.ray_dir_y;
	big->img.line_height = (int)(big->mys.r[1] / big->ray.perpwalldist);
	draw_start = -big->img.line_height / 2 + big->mys.r[1] / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = big->img.line_height / 2 + big->mys.r[1] / 2;
	if (draw_end >= big->mys.r[1])
		draw_end = big->mys.r[1] - 1;
	big->sp.z_buf[x] = big->ray.perpwalldist;
	ft_texturing(big, draw_start, draw_end, x);
	ft_draw_ceiling(big, draw_start, x, dst);
	ft_draw_floor(big, draw_end, x, dst);
}

int		ft_looping(t_master *big)
{
	int		x;
	float	temp[big->mys.r[0]];

	x = 0;
	big->sp.z_buf = temp;
	while (x < big->ray.w)
	{
		ft_find_variables(big, x);
		ft_find_sidedist(big);
		ft_dda(big);
		ft_wall_height(big, x);
		x++;
	}
	if (ft_sprite_put(big, 0) == -1)
		return (-1);
	if (big->mys.save != 0)
		return (ft_start_save(big));
	if (big->move.counter % 2 == 0)
		mlx_put_image_to_window(big->img.mlx, big->img.mlx_win,
		big->img.img, 0, 0);
	else
		mlx_put_image_to_window(big->img.mlx, big->img.mlx_win,
		big->sp.img, 0, 0);
	return (1);
}

int		start_raycastin(t_sto *mys)
{
	t_master	big;

	ft_sort_big_struct(&big, mys);
	big.img.mlx = mlx_init();
	check_resize(&big);
	if (big.mys.save == 0)
		big.img.mlx_win = mlx_new_window(big.img.mlx, big.mys.r[0],
		big.mys.r[1], "MLX");
	if (start_pos(&big, 0, 0) == -1)
		return (-1);
	if (ft_load_texture(&big) == -1)
		return (error_text(&big.mys, "error in texture", 0));
	if (ft_load_sprite(&big) == -1)
		return (-1);
	if (ft_looping(&big) == 2)
		return (1);
	mlx_hook(big.img.mlx_win, 02, 1L << 0, keypress, &big);
	mlx_hook(big.img.mlx_win, 03, 1L << 1, keyrelease, &big);
	mlx_hook(big.img.mlx_win, 17, 0L, exit_program, &big);
	mlx_loop_hook(big.img.mlx, keywhere, &big);
	mlx_loop(big.img.mlx);
	ft_zero_sprite_struct(&big.sp, 2);
	return (1);
}
