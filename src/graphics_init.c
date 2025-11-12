/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:54:09 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/12 10:54:44 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	init_mlx_connection(t_fdf *fdf)
{
	fdf->mlx->mlx_ptr = mlx_init();
	if (fdf->mlx->mlx_ptr == NULL)
		return (0);
	mlx_get_screen_size(fdf->mlx->mlx_ptr,
		&fdf->mlx->screen_width, &fdf->mlx->screen_height);
	return (1);
}

static int	init_window(t_fdf *fdf)
{
	fdf->mlx->win_ptr = mlx_new_window(fdf->mlx->mlx_ptr,
			fdf->mlx->screen_width, fdf->mlx->screen_height, WINDOW_TITLE);
	if (fdf->mlx->win_ptr == NULL)
		return (0);
	mlx_do_sync(fdf->mlx->mlx_ptr);
	return (1);
}

static int	init_image(t_fdf *fdf)
{
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr,
			fdf->mlx->screen_width, fdf->mlx->screen_height);
	if (fdf->mlx->img_ptr == NULL)
		return (0);
	fdf->mlx->img_data = mlx_get_data_addr(fdf->mlx->img_ptr,
			&fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	return (1);
}

int	init_graphics(t_fdf *fdf)
{
	fdf->mlx->mlx_ptr = NULL;
	fdf->mlx->win_ptr = NULL;
	fdf->mlx->img_ptr = NULL;
	if (!init_mlx_connection(fdf))
		return (0);
	if (!init_window(fdf))
	{
		free_resources(fdf);
		return (0);
	}
	if (!init_image(fdf))
	{
		free_resources(fdf);
		return (0);
	}
	return (1);
}

/*int	init_graphics(t_fdf *fdf)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (0);
	fdf->mlx->mlx_ptr = mlx_ptr;
	mlx_get_screen_size(fdf->mlx->mlx_ptr,
		&fdf->mlx->screen_width, &fdf->mlx->screen_height);
	fdf->mlx->win_ptr = mlx_new_window(fdf->mlx->mlx_ptr,
			fdf->mlx->screen_width, fdf->mlx->screen_height, WINDOW_TITLE);
	if (fdf->mlx->win_ptr == NULL)
		return (0);
	mlx_do_sync(fdf->mlx->mlx_ptr);
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr,
			fdf->mlx->screen_width, fdf->mlx->screen_height);
	if (fdf->mlx->img_ptr == NULL)
		return (0);
	fdf->mlx->img_data = mlx_get_data_addr(fdf->mlx->img_ptr,
			&fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	return (1);
}*/
