#include "../fdf.h"

int handle_keypress(int keycode, t_fdf *fdf)
{
    printf("Key pressed: %d\n", keycode);  // ADD THIS

    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
        exit(0);
    }

    if (keycode == 24)  // + key
    {
        printf("Zoom in!\n");  // ADD THIS
        fdf->camera->zoom += 2;
        redraw(fdf);
    }

	if (keycode == KEY_SPACE)  // Space to reset
	{
		fdf->camera->alpha = 0.0;
		fdf->camera->beta = 0.0;
		fdf->camera->zoom = 20;
		fdf->camera->x_offset = WINDOW_WIDTH / 2;
		fdf->camera->y_offset = WINDOW_HEIGHT / 2;
		redraw(fdf);
	}

	if (keycode == 27)  // - key
	{
		printf("Zoom out!\n");  // ADD THIS
		if (fdf->camera->zoom > 2)
			fdf->camera->zoom -= 2;
		redraw(fdf);
	}

    return (1);
}


int handle_mouse(int button, int x, int y, t_fdf *fdf)
{
    printf("Mouse button: %d at (%d, %d)\n", button, x, y);  // ADD THIS

    (void)x;
    (void)y;

    if (button == 4)  // Scroll up
    {
        printf("Scroll up - zoom in!\n");  // ADD THIS
        fdf->camera->zoom += 2;
        redraw(fdf);
    }
    else if (button == 5)  // Scroll down
    {
        printf("Scroll down - zoom out!\n");  // ADD THIS
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

