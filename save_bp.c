/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:41 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:08:50 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_find_me_color_save(t_master *big, int y, int x)
{
	char	*dst;

	dst = big->img.addr + (x * big->img.line_length + y *
	(big->img.bits_per_pixel / 8));
	big->sp.colour_save = *(unsigned int *)dst;
}

void	ft_putpixeldata(t_master *big)
{
	long int	x;
	long int	y;

	x = 0;
	y = big->mys.r[1] - 1;
	while (y >= 0)
	{
		while (x < big->mys.r[0])
		{
			ft_find_me_color_save(big, x, y);
			write(big->mys.save, &big->sp.colour_save, 3);
			write(big->mys.save, "0x00", 1);
			x++;
		}
		x = 0;
		y--;
	}
}

void	ft_infohader(t_master *big)
{
	unsigned char	buffer[40];
	int				i;
	int				width;
	int				height;

	width = big->mys.r[0];
	height = big->mys.r[1];
	i = 0;
	while (i < 40)
	{
		buffer[i] = (unsigned char)(0);
		i++;
	}
	buffer[0] = (unsigned char)(40);
	buffer[4] = (unsigned char)(width % 256);
	buffer[5] = (unsigned char)(width / 256 % 256);
	buffer[6] = (unsigned char)(width / 256 / 256 % 256);
	buffer[7] = (unsigned char)(width / 256 / 256 / 256);
	buffer[8] = (unsigned char)(height % 256);
	buffer[9] = (unsigned char)(height / 256 % 256);
	buffer[10] = (unsigned char)(height / 256 / 256 % 256);
	buffer[11] = (unsigned char)(height / 256 / 256 / 256);
	buffer[12] = (unsigned char)(1);
	buffer[14] = (unsigned char)(32);
	write(big->mys.save, buffer, 40);
}

void	ft_bitheader(t_master *big)
{
	int				i;
	unsigned char	buffer[14];
	unsigned int	filesize;

	i = 0;
	filesize = (big->mys.r[0] * big->mys.r[1] * 4 + 54);
	while (i < 14)
	{
		buffer[i] = (unsigned char)(0);
		i++;
	}
	buffer[0] = 'B';
	buffer[1] = 'M';
	buffer[2] = (unsigned char)(filesize % 256);
	buffer[3] = (unsigned char)(filesize / 256 % 256);
	buffer[4] = (unsigned char)(filesize / 256 / 256 % 256);
	buffer[5] = (unsigned char)(filesize / 256 / 256 / 256);
	buffer[10] = (unsigned char)(54);
	write(big->mys.save, buffer, 14);
}

int		ft_start_save(t_master *big)
{
	big->mys.save = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	ft_bitheader(big);
	ft_infohader(big);
	ft_putpixeldata(big);
	close(big->mys.save);
	return (2);
}
