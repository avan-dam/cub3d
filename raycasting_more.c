/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_more.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:50 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:08:33 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	check_resize(t_master *big)
{
	int	sizex;
	int	sizey;

	if (big->mys.save == 0)
	{
		mlx_get_screen_size(big->img.mlx, &sizex, &sizey);
		if (big->mys.r[0] >= sizex)
			big->mys.r[0] = sizex;
		if (big->mys.r[1] >= sizey)
			big->mys.r[1] = sizey;
	}
}

void	ft_loading_more(t_master *big)
{
	char	*end;

	end = ft_substr(big->mys.so, ft_strlen(big->mys.so) - 3, 3);
	if (ft_strcmp("png", end) == 0)
		big->img.texture2 = mlx_png_file_to_image(big->img.mlx, big->mys.so,
		&big->img.img_width2, &big->img.img_height2);
	else if (ft_strcmp("xpm", end) == 0)
		big->img.texture2 = mlx_xpm_file_to_image(big->img.mlx, big->mys.so,
		&big->img.img_width2, &big->img.img_height2);
	free(end);
	big->img.addrtexture2 = mlx_get_data_addr(big->img.texture2,
	&big->img.bits_per_pixel2, &big->img.line_length2, &big->img.endian);
	end = ft_substr(big->mys.we, ft_strlen(big->mys.we) - 3, 3);
	if (ft_strcmp("png", end) == 0)
		big->img.texture3 = mlx_png_file_to_image(big->img.mlx, big->mys.we,
		&big->img.img_width3, &big->img.img_height3);
	else if (ft_strcmp("xpm", end) == 0)
		big->img.texture3 = mlx_xpm_file_to_image(big->img.mlx, big->mys.we,
		&big->img.img_width3, &big->img.img_height3);
	free(end);
}

void	ft_loading_more_more(t_master *big)
{
	char	*end;

	big->img.addrtexture3 = mlx_get_data_addr(big->img.texture3,
	&big->img.bits_per_pixel3, &big->img.line_length3, &big->img.endian);
	end = ft_substr(big->mys.no, ft_strlen(big->mys.no) - 3, 3);
	if (ft_strcmp("png", end) == 0)
		big->img.texture4 = mlx_png_file_to_image(big->img.mlx, big->mys.no,
		&big->img.img_width4, &big->img.img_height4);
	else if (ft_strcmp("xpm", end) == 0)
		big->img.texture4 = mlx_xpm_file_to_image(big->img.mlx, big->mys.no,
		&big->img.img_width4, &big->img.img_height4);
	free(end);
	big->img.addrtexture4 = mlx_get_data_addr(big->img.texture4,
	&big->img.bits_per_pixel4, &big->img.line_length4, &big->img.endian);
	big->img.img = mlx_new_image(big->img.mlx, big->mys.r[0], big->mys.r[1]);
	big->img.addr = mlx_get_data_addr(big->img.img, &big->img.bits_per_pixel,
	&big->img.line_length, &big->img.endian);
	big->sp.img = mlx_new_image(big->img.mlx, big->mys.r[0], big->mys.r[1]);
	big->sp.addr = mlx_get_data_addr(big->sp.img,
	&big->img.bits_per_pixel, &big->img.line_length, &big->img.endian);
}

int		ft_load_texture(t_master *big)
{
	char	*end;

	end = ft_substr(big->mys.ea, ft_strlen(big->mys.ea) - 3, 3);
	if (ft_strcmp("png", end) == 0)
		big->img.texture1 = mlx_png_file_to_image(big->img.mlx, big->mys.ea,
		&big->img.img_width1, &big->img.img_height1);
	else if (ft_strcmp("xpm", end) == 0)
		big->img.texture1 = mlx_xpm_file_to_image(big->img.mlx, big->mys.ea,
		&big->img.img_width1, &big->img.img_height1);
	free(end);
	big->img.addrtexture1 = mlx_get_data_addr(big->img.texture1,
	&big->img.bits_per_pixel1, &big->img.line_length1, &big->img.endian);
	ft_loading_more(big);
	ft_loading_more_more(big);
	return (1);
}

void	ft_sort_big_struct(t_master *big, t_sto *mys)
{
	t_ray		ray;
	t_data		img;
	t_move		move;
	t_sprite	sp;

	ft_zero_tray(&ray);
	big->ray = ray;
	big->mys = *mys;
	ft_zero_tdata(&img);
	big->img = img;
	ft_zero_t_move(&move);
	big->move = move;
	ft_zero_sprite_struct(&sp, 1);
	big->sp = sp;
}
