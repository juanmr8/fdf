#include "../fdf.h"
// Empty for now
#include "../fdf.h"

void calculate_map_stats(t_map *map)
{
    int x;
	int y;

	x = 0;
	y = 0;
    if (map->height <= 0 || map->width <= 0)
        return;
	/*
		Rationale for initializing the code to the first value:
		What if all elevations are negative? Or all are above 100? Starting with 0 would give wrong results. Starting with the first actual value ensures we find the true minimum and maximum.
	*/
    map->z_min = map->z_matrix[0][0];
    map->z_max = map->z_matrix[0][0];

    // Your task: Complete the nested loops
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
	/*
		Rationale for this part:
		We'll use z_range to normalize colors and scale the wireframe properly. If range is 0-100, we know how to color-code heights. If range is 5-7, we need different scaling.
	*/
	map->z_range = map->z_max - map->z_min;
}

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
