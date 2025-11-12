/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:38:31 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/12 10:02:05 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_gradient_color(int z, t_map *map, t_fdf *fdf)
{
	double			percent;
	unsigned int	max;

	max = map->z_max - map->z_min;
	if (max == 0)
		return (0xF45B69);
	percent = ((double)(z - map->z_min) / max);
	if (fdf->camera->color_scheme == 0)
		return (get_gradient_one(percent));
	else if (fdf->camera->color_scheme == 1)
		return (get_gradient_two(percent));
	else if (fdf->camera->color_scheme == 2)
		return (get_gradient_three(percent));
	else if (fdf->camera->color_scheme == 3)
		return (get_gradient_four(percent));
	return (0xFFFFFF);
}

int	get_gradient_one(double percent)
{
	if (percent < 0.14)
		return (0xF45B69);
	else if (percent < 0.28)
		return (0xF06B6F);
	else if (percent < 0.42)
		return (0xEC7B75);
	else if (percent < 0.56)
		return (0xE88B7B);
	else if (percent < 0.70)
		return (0xE49B81);
	else if (percent < 0.84)
		return (0xE0AB87);
	else
		return (0xE4FDE1);
}

int	get_gradient_two(double percent)
{
	if (percent < 0.14)
		return (0x000080);
	else if (percent < 0.28)
		return (0x0047AB);
	else if (percent < 0.42)
		return (0x0077BE);
	else if (percent < 0.56)
		return (0x4682B4);
	else if (percent < 0.70)
		return (0x5F9EA0);
	else if (percent < 0.84)
		return (0x87CEEB);
	else
		return (0xAFEEEE);
}

int	get_gradient_three(double percent)
{
	if (percent < 0.14)
		return (0x013220);
	else if (percent < 0.28)
		return (0x014421);
	else if (percent < 0.42)
		return (0x228B22);
	else if (percent < 0.56)
		return (0x32CD32);
	else if (percent < 0.70)
		return (0x90EE90);
	else if (percent < 0.84)
		return (0x98FB98);
	else
		return (0xF0FFF0);
}

int	get_gradient_four(double percent)
{
	if (percent < 0.14)
		return (0x4B0082);
	else if (percent < 0.28)
		return (0x6A0DAD);
	else if (percent < 0.42)
		return (0x8B00FF);
	else if (percent < 0.56)
		return (0xDA70D6);
	else if (percent < 0.70)
		return (0xEE82EE);
	else if (percent < 0.84)
		return (0xFFB6C1);
	else
		return (0xFFF0F5);
}
