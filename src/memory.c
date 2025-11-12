/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:24:22 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/12 11:25:33 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	is_valid_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	allocate_map(t_map *map)
{
	int	i;
	int	*arr_width;

	i = 0;
	map->z_matrix = malloc(sizeof(int *) * map->height);
	if (!map->z_matrix)
		return (0);
	while (i < map->height)
	{
		arr_width = malloc(sizeof(int) * map->width);
		if (!arr_width)
		{
			while (--i >= 0)
				free(map->z_matrix[i]);
			free(map->z_matrix);
			return (0);
		}
		map->z_matrix[i] = arr_width;
		i++;
	}
	return (1);
}

static void	free_matrix(int **matrix, int height)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->z_matrix)
	{
		free_matrix(map->z_matrix, map->height);
		map->z_matrix = NULL;
	}
}

void	free_resources(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->mlx)
	{
		if (fdf->mlx->img_ptr)
			mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
		if (fdf->mlx->win_ptr)
			mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		if (fdf->mlx->mlx_ptr)
		{
			mlx_destroy_display(fdf->mlx->mlx_ptr);
			free(fdf->mlx->mlx_ptr);
			fdf->mlx->mlx_ptr = NULL;
		}
	}
	if (fdf->map)
		free_map(fdf->map);
}
