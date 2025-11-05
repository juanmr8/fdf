/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:01:54 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 17:03:11 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	rotate_around_x(float *y, float *z, float alpha)
{
	float	y_rot;
	float	z_rot;

	y_rot = *y * cos(alpha) - *z * sin(alpha);
	z_rot = *y * sin(alpha) + *z * cos(alpha);
	*y = y_rot;
	*z = z_rot;
}

static void	rotate_around_y(float *x, float *z, float beta)
{
	float	x_rot;
	float	z_rot;

	x_rot = *x * cos(beta) + *z * sin(beta);
	z_rot = -(*x) * sin(beta) + *z * cos(beta);
	*x = x_rot;
	*z = z_rot;
}

static void	to_isometric(float *x, float *y, float z, t_fdf *fdf)
{
	float	iso_x;
	float	iso_y;

	iso_x = (*x - *y) * cos(0.523599);
	iso_y = (*x + *y) * sin(0.523599) - z;
	iso_x = iso_x * fdf->camera->zoom;
	iso_y = iso_y * fdf->camera->zoom;
	*x = iso_x + fdf->camera->x_offset;
	*y = iso_y + fdf->camera->y_offset;
}

t_point	isometric_projection(float x, float y, t_fdf *fdf)
{
	t_point	result;
	float	z;

	z = fdf->map->z_matrix[(int)y][(int)x];
	x = x - fdf->map->width / 2.0;
	y = y - fdf->map->height / 2.0;
	rotate_around_x(&y, &z, fdf->camera->alpha);
	rotate_around_y(&x, &z, fdf->camera->beta);
	to_isometric(&x, &y, z, fdf);
	result.x = (int)x;
	result.y = (int)y;
	result.z = (int)z;
	return (result);
}
