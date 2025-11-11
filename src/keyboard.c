/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:51:52 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/11 15:07:16 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	reset_camera(t_fdf *fdf)
{
	fdf->camera->alpha = 0.0;
	fdf->camera->beta = 0.0;
	fdf->camera->zoom = 20;
	fdf->camera->x_offset = fdf->mlx->screen_width / 2;
	fdf->camera->y_offset = fdf->mlx->screen_height / 2;
}

void	handle_zoom_and_reset(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_PLUS)
	{
		fdf->camera->zoom += 2;
		redraw(fdf);
	}
	else if (keycode == KEY_MINUS)
	{
		if (fdf->camera->zoom > 2)
			fdf->camera->zoom -= 2;
		redraw(fdf);
	}
	else if (keycode == KEY_SPACE)
	{
		reset_camera(fdf);
		redraw(fdf);
	}
}

static int	process_color_key(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_1)
		handle_key_number(0, fdf);
	else if (keycode == KEY_2)
		handle_key_number(1, fdf);
	else if (keycode == KEY_3)
		handle_key_number(2, fdf);
	else if (keycode == KEY_4)
		handle_key_number(3, fdf);
	else if (keycode == KEY_5)
		handle_key_number(4, fdf);
	else
		return (0);
	return (1);
}

int	handle_color_keys(int keycode, t_fdf *fdf)
{
	return (process_color_key(keycode, fdf));
}

void	handle_key_number(int scheme, t_fdf *fdf)
{
	fdf->camera->color_scheme = scheme;
	redraw(fdf);
}
