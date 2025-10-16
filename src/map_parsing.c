#include "../fdf.h"

// Count how many numbers are in a line
int count_words(char *str, char delimiter)
{
    int count = 0;
    int in_word = 0;

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

// Count how many rows and columns are in the file
int get_map_dimensions(char *filename, int *width, int *height)
{
    int fd;
    char *line;
    int width_counter;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);

    *width = 0;
    *height = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        width_counter = count_words(line, ' ');
        if (width_counter > *width)
            *width = width_counter;
        (*height)++;
        free(line);
    }
    close(fd);
    return (1);
}

int parse_map_data(char *filename, t_map *map)
{
	int fd;
	char *line;
	char **numbers;
	int	x;
	int y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	while ((line = get_next_line(fd)) != NULL && y < map->height)
	{
		numbers = ft_split(line, ' ');
		if (!numbers)
		{
			free(line);
			close(fd);
			return (0);
		}
		x = 0;
		while (numbers[x] && x < map->width)
		{
			map->z_matrix[y][x] = ft_atoi(numbers[x]);
			free(numbers[x]);
			x++;
		}
		free(numbers);
		free(line);
		y++;
	}
	close(fd);
	return (1);
}
