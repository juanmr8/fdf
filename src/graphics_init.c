#include "../fdf.h"

int init_graphics(t_fdf *fdf)
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (0);
	fdf->mlx->mlx_ptr = mlx_ptr;

	// Create window
	fdf->mlx->win_ptr = mlx_new_window(fdf->mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	if (fdf->mlx->win_ptr == NULL)
		return (0);
	mlx_do_sync(fdf->mlx->mlx_ptr);

	// Create image buffer
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (fdf->mlx->img_ptr == NULL)
		return (0);

	// Get image data address
	fdf->mlx->img_data = mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);

	return (1);
}
