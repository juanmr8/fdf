/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:24:22 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/03 16:10:23 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Function 1: Show error and exit
void error_exit(char *message)
{
    ft_printf("Error: %s\n", message);
    exit(1);
}

// Function 2: Show how to use the program
void usage(void)
{
    ft_printf("Usage: fdf <filename.fdf>\n");
}

// Function 3: Check if file exists and can be opened
int is_valid_file(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}


// ========== NEW FUNCTION TO ADD ==========
// Allocate memory for the 2D map array
int allocate_map(t_map *map)
{
    // Step 1: Declare variables [x]
	int i;
	int *arr_width;
    // - loop counter (int)

	i = 0;
    // Step 2: Allocate array of row pointers [x]
	map->z_matrix = malloc(sizeof(int *) * map->height);
	if (!map->z_matrix)
		return (0);
    // - Use malloc to create array of (int *) pointers [x]
    // - Size: sizeof(int *) * map->height [x]
    // - Store in map->z_matrix
    // - Check if malloc failed (returns NULL)


    // Step 3: Allocate each individual row
	while (i < map->height)
	{
		arr_width = malloc(sizeof(int) * map->width);
		if (!arr_width)
		{
			while (--i >= 0)
				free(map->z_matrix[i]);
			free(map->z_matrix);
			return (0);
		}
		map->z_matrix[i] = arr_width;
		i++;
	}
    // - Use for loop from 0 to map->height
    // - For each row: malloc array of integers
    // - Size: sizeof(int) * map->width
    // - Store in map->z_matrix[i]
    // - If malloc fails: free all previous rows and return 0


    // Step 4: Return success [x]
	return (1);
    // - Return 1

}
