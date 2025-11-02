/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:38:31 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/02 16:09:34 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_gradient_color(int z, t_map *map)
{
    double            percent;
    unsigned int    max;

    max = map->z_max - map->z_min;
    if (max == 0)
        return (0xF45B69);
    percent = ((double)(z - map->z_min) / max);
    if (percent < 0.14)
        return (0xF45B69);  // Bright red-pink
    else if (percent < 0.28)
        return (0xF06B6F);  // Red-orange
    else if (percent < 0.42)
        return (0xEC7B75);  // Orange-red
    else if (percent < 0.56)
        return (0xE88B7B);  // Light orange
    else if (percent < 0.70)
        return (0xE49B81);  // Peach
    else if (percent < 0.84)
        return (0xE0AB87);  // Light peach
    else
        return (0xE4FDE1);  // Very light green
}

void	get_gradient_by_num(int num, double percent)
{
	if (num == 1)
		get_gradient_two(percent);
	else if (num == 2)
		get_gradient_three(percent);
	else if (num == 3)
		get_gradient_four(percent);
	else
		get_gradient_one(percent);
}

int	get_gradient_one(double percent)
{

}

int	get_gradient_two(double percent)
{

}

int	get_gradient_three(double percent)
{

}

int	get_gradient_four(double percent)
{

}
