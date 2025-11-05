/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:24:26 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 16:40:07 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	calculate_map_stats(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (map->height <= 0 || map->width <= 0)
		return ;
	map->z_min = map->z_matrix[0][0];
	map->z_max = map->z_matrix[0][0];
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->z_min > map->z_matrix[y][x])
				map->z_min = map->z_matrix[y][x];
			if (map->z_max < map->z_matrix[y][x])
				map->z_max = map->z_matrix[y][x];
			x++;
		}
		y++;
	}
	map->z_range = map->z_max - map->z_min;
}

int	count_words(char *str, char delimiter)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == delimiter || *str == '\n')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

int	get_map_dimensions(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	int		width_counter;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		width_counter = count_words(line, ' ');
		if (width_counter > *width)
			*width = width_counter;
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
