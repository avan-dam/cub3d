/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites_more.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:41 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/08 17:34:51 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_store_sprite(t_master *big)
{
	int	x;
	int	y;
	int	j;

	x = 0;
	y = 0;
	j = 0;
	while (x < big->mys.row)
	{
		while (big->mys.split[x][y] != '\0')
		{
			if (big->mys.split[x][y] == '2')
			{
				big->sprite.sprites[j][0] = x;
				big->sprite.sprites[j][1] = y;
				j++;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	ft_numb_sprites(t_master *big)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < big->mys.row)
	{
		while (big->mys.split[x][y] != '\0')
		{
			if (big->mys.split[x][y] == '2')
				big->sprite.numbsprite++;
			y++;
		}
		y = 0;
		x++;
	}
	big->sprite.sprites = (int**)malloc(sizeof(int*) *
	(big->sprite.numbsprite + 1));
	x = 0;
	while (x < big->sprite.numbsprite)
	{
		big->sprite.sprites[x] = (int *)malloc(sizeof(int) * 2);
		x++;
	}
	ft_store_sprite(big);
}

void	ft_find_me_sprite_color(t_master *big, int tex_x, int y)
{
	char	*dst;
	int		d;
	int		tex_y;

	d = (y) * 256 - big->mys.r[1] * 128 + big->sprite.height * 128;
	tex_y = (int)(((d * big->img.img_height5) / big->sprite.height) / 256);
	dst = big->img.addrsprite + (tex_y * big->img.line_length5 + tex_x *
	(big->img.bits_per_pixel5 / 8));
	big->img.color_sprite = *(unsigned int *)dst;
}

void	ver_dot_sprite(int x, int y, t_master *big)
{
	char	*dst;

	// if (big->img.color_sprite != 0x00FFFFFF)
	// {
		dst = big->img.addr + (y * big->img.line_length + x *
		(big->img.bits_per_pixel / 8));
		*(unsigned int*)dst = big->img.color_sprite;
	// }
}

void	ft_load_sprite(t_master *big)
{
	big->img.sprite = mlx_png_file_to_image(big->img.mlx, big->mys.s,
	&big->img.img_width5, &big->img.img_height5);
	big->img.addrsprite = mlx_get_data_addr(big->img.sprite,
	&big->img.bits_per_pixel5, &big->img.line_length5, &big->img.endian);
}
