/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:39:14 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/12 10:17:52 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->screen_width)
		return ;
	if (y < 0 || y >= mlx->screen_height)
		return ;
	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = mlx_get_color_value(mlx->mlx_ptr, color);
}

void	draw_line(t_point start, t_point end, t_fdf *fdf, int color)
{
	t_line	line;
	int		x;
	int		y;
	int		e2;

	line = init_line(start, end);
	x = start.x;
	y = start.y;
	while (1)
	{
		put_pixel(fdf->mlx, x, y, color);
		if (x == end.x && y == end.y)
			break ;
		e2 = line.err * 2;
		if (e2 > -line.dy)
		{
			line.err -= line.dy;
			x += line.sx;
		}
		if (e2 < line.dx)
		{
			line.err += line.dx;
			y += line.sy;
		}
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			draw_horizontal_lines(fdf, x, y);
			draw_vertical_lines(fdf, x, y);
			x++;
		}
		y++;
	}
}

void	redraw(t_fdf *fdf)
{
	int	total_bytes;

	total_bytes = fdf->mlx->screen_width
		* fdf->mlx->screen_height * (fdf->mlx->bpp / 8);
	ft_bzero(fdf->mlx->img_data, total_bytes);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx->mlx_ptr,
		fdf->mlx->win_ptr, fdf->mlx->img_ptr, 0, 0);
	ft_write_guide(fdf);
}
