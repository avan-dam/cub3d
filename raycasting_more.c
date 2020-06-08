/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_more.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:50 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/08 16:36:45 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		closeme(int keycode, t_master *big)
{
	if (keycode == 53)
	{
		mlx_clear_window(big->img.mlx, big->img.mlx_win);
		mlx_destroy_window(big->img.mlx, big->img.mlx_win);
		exit(0);
	}
	return (0);
}

int		exit_program(t_master *big)
{
	mlx_destroy_window(big->img.mlx, big->img.mlx_win);
	exit(0);
	return (0);
}

void	ft_load_texture(t_master *big)
{
	big->img.texture1 = mlx_png_file_to_image(big->img.mlx, big->mys.we,
	&big->img.img_width1, &big->img.img_height1);
	big->img.addrtexture1 = mlx_get_data_addr(big->img.texture1,
	&big->img.bits_per_pixel1, &big->img.line_length1, &big->img.endian);
	big->img.texture2 = mlx_png_file_to_image(big->img.mlx, big->mys.no,
	&big->img.img_width2, &big->img.img_height2);
	big->img.addrtexture2 = mlx_get_data_addr(big->img.texture2,
	&big->img.bits_per_pixel2, &big->img.line_length2, &big->img.endian);
	big->img.texture3 = mlx_png_file_to_image(big->img.mlx, big->mys.ea,
	&big->img.img_width3, &big->img.img_height3);
	big->img.addrtexture3 = mlx_get_data_addr(big->img.texture3,
	&big->img.bits_per_pixel3, &big->img.line_length3, &big->img.endian);
	big->img.texture4 = mlx_png_file_to_image(big->img.mlx, big->mys.so,
	&big->img.img_width4, &big->img.img_height4);
	big->img.addrtexture4 = mlx_get_data_addr(big->img.texture4,
	&big->img.bits_per_pixel4, &big->img.line_length4, &big->img.endian);
	big->img.img = mlx_new_image(big->img.mlx, big->mys.r[0], big->mys.r[1]);
	big->img.addr = mlx_get_data_addr(big->img.img, &big->img.bits_per_pixel,
	&big->img.line_length, &big->img.endian);
}

void	ft_sort_big_struct(t_master *big, t_sto *mys)
{
	t_ray		ray;
	t_data		img;
	t_move		move;
	t_sprite	sprite;

	ft_zero_tray(&ray);
	big->ray = ray;
	big->mys = *mys;
	ft_zero_tdata(&img);
	big->img = img;
	ft_zero_t_move(&move);
	big->move = move;
	ft_zero_sprite_struct(&sprite, 1);
	big->sprite = sprite;
}
