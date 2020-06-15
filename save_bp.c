/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 16:58:41 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/15 19:39:12 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

char	*ft_bzero_cub3d(int n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(n);
	if (ptr == NULL)
		return (NULL);
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	ft_puthx(long int i, int fd)
{
	char		z;
	long int	c;

	c = i;
	while (c >= 16)
		c = c / 16;
	if (i >= 16)
	{
		ft_puthx(i / 16, fd);
		ft_puthx(i % 16, fd);
	}
	else
	{
		if (i <= 9)
			z = i + '0';
		else
			z = (i - 10) + 'A';
		write(fd, &z, 1);
	}
}

int		ft_len_hx(long int i)
{
	long int	a;

	a = 0;
	if (i < 0)
	{
		i = i * -1;
		i = 4294967296 - i;
	}
	while (i >= 16)
	{
		i = i / 16;
		a++;
	}
	a++;
	return (a);
}

void	ft_padding(int fd, int len)
{
	int i;

	i = 0;
	while (i < 16 - 2 - len)
	{
		write(fd, "0", 1);
		i++;
	}
}

void     ft_bitheader(t_master *big)
{    //24 bits-per-pixel bitmap (BGR)
	int	width_len;
	int	height_len;
	long int imgsize;
	int imgsize_len;
	int i;

	i = 0;
	width_len = ft_len_hx(big->mys.r[0]);
	height_len = ft_len_hx(big->mys.r[1]);
	imgsize = big->mys.r[0] * big->mys.r[1];
	imgsize_len = ft_len_hx(imgsize);
    write(big->mys.save, "0x420x4D", 8);//file type
	write(big->mys.save, "0x000x000x000x00", 16);//file size
	write(big->mys.save, "0x000x000x000x00", 16);//reserved
	write(big->mys.save, "0x000x000x000x00", 16);//reserved
	write(big->mys.save, "0x360x000x000x00", 16);//54 pixeloffsetdata
	write(big->mys.save, "0x280x000x000x00", 16);//40 headersize
	write(big->mys.save, "0x", 2);//imagewidth
	ft_puthx(big->mys.r[0], big->mys.save);
	ft_padding(big->mys.save, width_len);
	write(big->mys.save, "0x", 2);//imagewidth
	ft_puthx(big->mys.r[1], big->mys.save);
	ft_padding(big->mys.save, height_len);
	write(big->mys.save, "0x010x00", 8);//Planes 1 color plane
	write(big->mys.save, "0x180x00", 8);//24 bits per pixel
	write(big->mys.save, "0x000x000x000x00", 16);//compression
	write(big->mys.save, "0x", 2);//imagesize
	ft_puthx(imgsize, big->mys.save);
	ft_padding(big->mys.save, imgsize_len);
	write(big->mys.save, "0x000x000x000x00", 16);//XpixelsPerMeter
	write(big->mys.save, "0x000x000x000x00", 16);//YpixelsPerMeter
	write(big->mys.save, "0x000x000x000x00", 16);//Totalcolors
	write(big->mys.save, "0x000x000x000x00", 16);//importantColors
}

int     ft_start_save(t_master *big)
{
    ft_bitheader(big);
    // close(big->mys.save);
    return (1);
}
