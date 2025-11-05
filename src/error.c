/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:42:05 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 16:42:07 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void error_exit(char *message)
{
	ft_printf("Error: %s\n", message);
	exit(1);
}

void usage(void)
{
    ft_printf("Usage: fdf <filename.fdf>\n");
}
