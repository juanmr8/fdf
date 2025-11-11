/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:57:05 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/06 12:20:44 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_map	init_map(t_map *map, char **argv)
{
	map->width = 0;
	map->height = 0;
	map->z_matrix = NULL;
	map->color_matrix = NULL;
	map->z_min = 0;
	map->z_max = 0;
	map->z_range = 0;
	if (!get_map_dimensions(argv[1], &map->width, &map->height))
		error_exit("Failed to get dimensions");
	if (!allocate_map(map))
		error_exit("Failed to allocate memory");
	if (!parse_map_data(argv[1], map))
		error_exit("Failed to parse map data");
	calculate_map_stats(map);
	return (*map);
}

static	t_camera	init_camera(t_camera *camera, t_fdf *fdf)
{
	camera->zoom = 20;
	camera->x_offset = fdf->mlx->screen_width / 2;
	camera->y_offset = fdf->mlx->screen_height / 2;
	camera->z_scale = 1;
	camera->alpha = 0.0;
	camera->beta = 0.0;
	camera->gamma = 0.0;
	camera->projection = 0;
	camera->color_scheme = 0;
	return (*camera);
}

static	t_fdf	init_fdf(t_fdf *fdf, t_map *map, t_mlx *mlx, t_camera *camera)
{
	fdf->map = map;
	fdf->mlx = mlx;
	fdf->camera = camera;
	fdf->mouse.right_button_down = 0;
	fdf->mouse.left_button_down = 0;
	fdf->mouse.last_x = 0;
	fdf->mouse.last_y = 0;
	return (*fdf);
}

static void	first_paint(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr,
		fdf->mlx->img_ptr, 0, 0);
	ft_write_guide(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	t_map		map;
	t_mlx		mlx;
	t_camera	camera;

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
	map = init_map(&map, argv);
	fdf = init_fdf(&fdf, &map, &mlx, &camera);
	if (!init_graphics(&fdf))
		error_exit("Failed to initialize graphics");
	camera = init_camera(&camera, &fdf);
	first_paint(&fdf);
	init_hooks(&fdf);
	mlx_loop(fdf.mlx->mlx_ptr);
	return (0);
}
