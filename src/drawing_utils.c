/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:38:58 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/02 15:38:59 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void ft_write_guide(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20, (WINDOW_HEIGHT - 50), 0xFFFFFF, "Right Click + Drag to Rotate");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20, (WINDOW_HEIGHT - 70), 0xFFFFFF, "Left Click + Drag to Pan");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20, (WINDOW_HEIGHT - 90), 0xFFFFFF, "Use '+' and '-' for zoom");
	mlx_string_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, 20, (WINDOW_HEIGHT - 110), 0xFFFFFF, "Use scroll for zoom");
}
