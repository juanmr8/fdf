/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:10:00 by auto               #+#    #+#             */
/*   Updated: 2025/11/05 15:10:00 by auto               ###   ########.fr       */
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

int		handle_color_keys(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_1)
	{
		handle_key_number(0, fdf);
		return (1);
	}
	else if (keycode == KEY_2)
	{
		handle_key_number(1, fdf);
		return (1);
	}
	else if (keycode == KEY_3)
	{
		handle_key_number(2, fdf);
		return (1);
	}
	else if (keycode == KEY_4)
	{
		handle_key_number(3, fdf);
		return (1);
	}
	else if (keycode == KEY_5)
	{
		handle_key_number(4, fdf);
		return (1);
	}
	return (0);
}

void	handle_key_number(int scheme, t_fdf *fdf)
{
	fdf->camera->color_scheme = scheme;
	redraw(fdf);
}


