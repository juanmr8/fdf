/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:21:40 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/05 15:32:42 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	open_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

static void	free_number_array(char **numbers, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

static int	parse_map_line(char **numbers, t_map *map, int y)
{
	int	x;

	x = 0;
	while (numbers[x] && x < map->width)
	{
		map->z_matrix[y][x] = ft_atoi(numbers[x]);
		x++;
	}
	return (x);
}

static int	process_line(char *line, t_map *map, int y)
{
	char	**numbers;
	int		result;

	numbers = ft_split(line, ' ');
	if (!numbers)
		return (0);
	result = parse_map_line(numbers, map, y);
	free_number_array(numbers, map->width);
	return (result);
}

int	parse_map_data(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		y;

	fd = open_map_file(filename);
	if (fd < 0)
		return (0);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL && y < map->height)
	{
		if (!process_line(line, map, y))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
