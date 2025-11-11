/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:46:11 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/11 14:57:31 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		free_resources(fdf);
		exit(0);
	}
	handle_zoom_and_reset(keycode, fdf);
	if (handle_color_keys(keycode, fdf))
		return (1);
	return (1);
}

int	handle_mouse(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->camera->zoom += 2;
		redraw(fdf);
	}
	else if (button == 5)
	{
		if (fdf->camera->zoom > 2)
			fdf->camera->zoom -= 2;
		redraw(fdf);
	}
	return (0);
}

int	handle_close(t_fdf *fdf)
{
	free_resources(fdf);
	exit (0);
}

void	init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx->win_ptr, 2, 1L << 0, handle_keypress, fdf);
	mlx_hook(fdf->mlx->win_ptr, 17, 0, handle_close, fdf);
	mlx_hook(fdf->mlx->win_ptr, 4, 1L << 2, handle_mouse_button, fdf);
	mlx_hook(fdf->mlx->win_ptr, 5, 1L << 3, handle_mouse_release, fdf);
	mlx_hook(fdf->mlx->win_ptr, 6, 1L << 6, handle_mouse_motion, fdf);
}
