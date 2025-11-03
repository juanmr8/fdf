#include "../fdf.h"

int handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		exit(0);
	}

	if (keycode == KEY_PLUS)
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

	if (keycode == KEY_MINUS)
	{
		if (fdf->camera->zoom > 2)
			fdf->camera->zoom -= 2;
		redraw(fdf);
	}
	if (keycode == KEY_1)
	{
		fdf->camera->color_scheme = 0;
		redraw(fdf);
	}
	else if (keycode == KEY_2)
	{
		fdf->camera->color_scheme = 1;
		redraw(fdf);
	}
	else if (keycode == KEY_3)
	{
		fdf->camera->color_scheme = 2;
		redraw(fdf);
	}
	else if (keycode == KEY_4)
	{
		fdf->camera->color_scheme = 3;
		redraw(fdf);
	}
	else if (keycode == KEY_5)
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
	mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	free(fdf->camera);

	exit (0);
}

void init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx->win_ptr, 2, 1L<<0, handle_keypress, fdf);
	mlx_hook(fdf->mlx->win_ptr, 17, 0, handle_close, fdf);
	mlx_hook(fdf->mlx->win_ptr, 4, 1L<<2, handle_mouse_button, fdf);
	mlx_hook(fdf->mlx->win_ptr, 5, 1L<<3, handle_mouse_release, fdf);
	mlx_hook(fdf->mlx->win_ptr, 6, 1L<<6, handle_mouse_motion, fdf);
}
