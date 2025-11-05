/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:01:48 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 16:50:12 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	handle_mouse_button(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->mouse.left_button_down = 1;
		fdf->mouse.last_x = x;
		fdf->mouse.last_y = y;
	}
	if (button == 3)
	{
		fdf->mouse.right_button_down = 1;
		fdf->mouse.last_x = x;
		fdf->mouse.last_y = y;
	}
	else if (button == 4)
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

int	handle_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->mouse.left_button_down = 0;
	else if (button == 3)
		fdf->mouse.right_button_down = 0;
	return (0);
}

static void	handle_mouse_left_button(int x, int y, t_fdf *fdf)
{
	int	delta_x;
	int	delta_y;

	delta_x = x - fdf->mouse.last_x;
	delta_y = y - fdf->mouse.last_y;
	fdf->camera->x_offset += delta_x;
	fdf->camera->y_offset += delta_y;
	fdf->mouse.last_x = x;
	fdf->mouse.last_y = y;
	redraw(fdf);
}

static void	handle_mouse_right_button(int x, int y, t_fdf *fdf)
{
	int	delta_x;
	int	delta_y;

	delta_x = x - fdf->mouse.last_x;
	delta_y = y - fdf->mouse.last_y;
	fdf->camera->beta += delta_x * 0.01;
	fdf->camera->alpha += delta_y * 0.01;
	fdf->mouse.last_x = x;
	fdf->mouse.last_y = y;
	redraw(fdf);
}

int	handle_mouse_motion(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse.left_button_down)
	{
		handle_mouse_left_button(x, y, fdf);
		return (0);
	}
	if (fdf->mouse.right_button_down)
	{
		handle_mouse_right_button(x, y, fdf);
		return (0);
	}
	return (0);
}
