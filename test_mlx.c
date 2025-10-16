/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:40:00 by your_username    #+#    #+#             */
/*   Updated: 2025/01/15 17:40:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define KEY_ESC 53

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_data;

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_test_pattern(t_data *data)
{
    int x, y;

    // Clear background to black
    for (y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            put_pixel(data, x, y, 0x000000);
        }
    }

    // Draw colored rectangles
    for (y = 100; y < 200; y++)
    {
        for (x = 100; x < 200; x++)
        {
            put_pixel(data, x, y, 0xFF0000); // Red
        }
    }

    for (y = 100; y < 200; y++)
    {
        for (x = 300; x < 400; x++)
        {
            put_pixel(data, x, y, 0x00FF00); // Green
        }
    }

    for (y = 100; y < 200; y++)
    {
        for (x = 500; x < 600; x++)
        {
            put_pixel(data, x, y, 0x0000FF); // Blue
        }
    }

    // Draw a white cross in the center
    int center_x = WINDOW_WIDTH / 2;
    int center_y = WINDOW_HEIGHT / 2;

    for (int i = -50; i <= 50; i++)
    {
        put_pixel(data, center_x + i, center_y, 0xFFFFFF);
        put_pixel(data, center_x, center_y + i, 0xFFFFFF);
    }
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    printf("Key pressed: %d\n", keycode);
    return (0);
}

int close_hook(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int main(void)
{
    t_data data;

    printf("Initializing MiniLibX test...\n");

    // Initialize MLX
    data.mlx = mlx_init();
    if (!data.mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        return (1);
    }

    // Create window
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF Test");
    if (!data.win)
    {
        printf("Error: Failed to create window\n");
        return (1);
    }

    // Create image
    data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!data.img)
    {
        printf("Error: Failed to create image\n");
        return (1);
    }

    // Get image data
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);

    printf("✓ MiniLibX initialized successfully!\n");
    printf("Window: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Image: bpp=%d, line_len=%d, endian=%d\n", data.bpp, data.line_len, data.endian);
    printf("Press ESC to exit or close the window.\n");

    // Draw test pattern
    draw_test_pattern(&data);

    // Display image
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

    // Set up hooks
    mlx_key_hook(data.win, key_hook, &data);
    mlx_hook(data.win, 17, 0, close_hook, &data);

    // Start event loop
    mlx_loop(data.mlx);

    return (0);
}
