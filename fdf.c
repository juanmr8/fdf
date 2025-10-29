#include "fdf.h"

int main(int argc, char **argv)
{
	t_fdf fdf;
    t_map map;
    t_mlx mlx;

	fdf.map = &map;
    fdf.mlx = &mlx;
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

	printf("✓ Wireframe rendered!\n");
	/**
	 * Here we using callbacks from MinilibX - They he
	 */
	// This one handles any keypress - particularly the ESC as we use it to close
	mlx_key_hook(fdf.mlx->win_ptr, handle_keypress, &fdf);
	// This one handles clicking the button X on the window
	mlx_hook(fdf.mlx->win_ptr, 17, 0, handle_close, &fdf);
	// This handles event listening overall - is watching
	mlx_loop(fdf.mlx->mlx_ptr);


	// Cleanup (only reached after mlx_loop exits)
	return (0);
}
