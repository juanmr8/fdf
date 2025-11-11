/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:38:58 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 14:40:22 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_write_guide(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20,
		(fdf->mlx->screen_height - 50), 0xFFFFFF, "Right Click + Drag to Rotate");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20,
		(fdf->mlx->screen_height - 70), 0xFFFFFF, "Left Click + Drag to Pan");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20,
		(fdf->mlx->screen_height - 90), 0xFFFFFF, "Use '+' and '-' for zoom");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20,
		(fdf->mlx->screen_height - 110), 0xFFFFFF, "Use scroll for zoom");
}

t_line	init_line(t_point start, t_point end)
{
	t_line	line;

	line.dx = abs(end.x - start.x);
	line.dy = abs(end.y - start.y);
	if (start.x < end.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (start.y < end.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	return (line);
}

void	draw_horizontal_lines(t_fdf *fdf, int x, int y)
{
	t_point	current;
	t_point	right;
	int		color;

	if (x < fdf->map->width - 1)
	{
		current = isometric_projection(x, y, fdf);
		right = isometric_projection(x + 1, y, fdf);
		color = get_gradient_color(fdf->map->z_matrix[y][x], fdf->map, fdf);
		draw_line(current, right, fdf, color);
	}
}

void	draw_vertical_lines(t_fdf *fdf, int x, int y)
{
	t_point	current;
	t_point	down;
	int		color;

	if (y < fdf->map->height -1)
	{
		current = isometric_projection(x, y, fdf);
		down = isometric_projection(x, y + 1, fdf);
		color = get_gradient_color(fdf->map->z_matrix[y][x], fdf->map, fdf);
		draw_line(current, down, fdf, color);
	}
}
