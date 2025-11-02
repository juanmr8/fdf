#include "fdf.h"

int main(int argc, char **argv)
{
	t_fdf	fdf;
    t_map	map;
    t_mlx	mlx;
	t_camera	camera;

	fdf.map = &map;
    fdf.mlx = &mlx;
	fdf.camera = &camera;
	camera.alpha = 0.0;    // ADD THIS
	camera.beta = 0.0;     // ADD THIS
	camera.gamma = 0.0;    // ADD THIS
	fdf.mouse.right_button_down = 0;  // ADD THIS
	fdf.mouse.left_button_down = 0;
	fdf.mouse.last_x = 0;              // ADD THIS
	fdf.mouse.last_y = 0;              // ADD THIS

    if (argc != 2)
    {
        usage();
        return (1);
    }

    if (!is_valid_file(argv[1]))
    {
        error_exit("Cannot read file");
        return (1);
    }

    printf("✓ File %s is valid!\n", argv[1]);

    // Test dimensions
    if (get_map_dimensions(argv[1], &map.width, &map.height))
    {
        printf("✓ Map dimensions: %dx%d\n", map.width, map.height);
    }
    else
    {
        error_exit("Failed to get dimensions");
    }
    // Test memory allocation
    if (allocate_map(&map))
    {
        printf("✓ Memory allocated for %dx%d map\n", map.width, map.height);
        printf("✓ Ready to store %d total numbers\n", map.width * map.height);
	}
	else
	{
		error_exit("Failed to allocate memory");
	}
	camera.zoom = 20;
	camera.x_offset = WINDOW_WIDTH / 2;
	camera.y_offset = WINDOW_HEIGHT / 2;
	// In main, after parse_map_data succeeds:
	if (parse_map_data(argv[1], &map))
	{
		printf("✓ Map data loaded successfully\n");

		calculate_map_stats(&map);
		printf("✓ Map statistics: Z-range %d to %d (range: %d)\n",
			map.z_min, map.z_max, map.z_range);
	}

	if (!init_graphics(&fdf))
		error_exit("Failed to initialize graphics");

	printf("✓ Graphics initialized successfully\n");

	draw_map(&fdf);
	mlx_put_image_to_window(fdf.mlx->mlx_ptr, fdf.mlx->win_ptr, fdf.mlx->img_ptr, 0, 0);
	ft_write_guide(&fdf);


	printf("✓ Wireframe rendered!\n");
	/**
	 * Here we using callbacks from MinilibX - They he
	 */
	mlx_hook(fdf.mlx->win_ptr, 2, 0, handle_keypress, &fdf);
	mlx_hook(fdf.mlx->win_ptr, 17, 0, handle_close, &fdf);
	mlx_hook(fdf.mlx->win_ptr, 4, 0, handle_mouse_button, &fdf);   // Press
	mlx_hook(fdf.mlx->win_ptr, 5, 0, handle_mouse_release, &fdf);  // Release
	mlx_hook(fdf.mlx->win_ptr, 6, 0, handle_mouse_motion, &fdf);   // Motion
	// Start event loop
	mlx_loop(fdf.mlx->mlx_ptr);

	// Cleanup (only reached after mlx_loop exits)
	return (0);
}
