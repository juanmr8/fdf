#include "../fdf.h"
#define KEY_ESC 53

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		exit (0);
	}
	return (1);
}

int handle_close(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	exit (0);
}
