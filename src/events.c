#include "../fdf.h"

int handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		exit(0);
	}

	if (keycode == 24)
	{
		fdf->camera->zoom += 2;
		redraw(fdf);
	}
	if (keycode == KEY_SPACE)
	{
		fdf->camera->alpha = 0.0;
		fdf->camera->beta = 0.0;
		fdf->camera->zoom = 20;
		fdf->camera->x_offset = WINDOW_WIDTH / 2;
		fdf->camera->y_offset = WINDOW_HEIGHT / 2;
		redraw(fdf);
	}

	if (keycode == 27)
	{
		if (fdf->camera->zoom > 2)
			fdf->camera->zoom -= 2;
		redraw(fdf);
	}
	if (keycode == 18)
	{
		fdf->camera->color_scheme = 0;
		redraw(fdf);
	}
	else if (keycode == 19)
	{
		fdf->camera->color_scheme = 1;
		redraw(fdf);
	}
	else if (keycode == 20)
	{
		fdf->camera->color_scheme = 2;
		redraw(fdf);
	}
	else if (keycode == 21)
	{
		fdf->camera->color_scheme = 3;
		redraw(fdf);
	}
	else if (keycode == 23)
	{
		fdf->camera->color_scheme = 4;
		redraw(fdf);
	}
    return (1);
}


int handle_mouse(int button, int x, int y, t_fdf *fdf)
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


int handle_close(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	exit (0);
}

