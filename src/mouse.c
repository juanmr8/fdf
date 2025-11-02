/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:01:48 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/02 14:52:05 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
// Single handler for button press
int handle_mouse_button(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)  // Left click pressed - ADD THIS BLOCK
    {
        fdf->mouse.left_button_down = 1;
        fdf->mouse.last_x = x;
        fdf->mouse.last_y = y;
    }
    if (button == 2)  // Right click pressed
    {
        fdf->mouse.right_button_down = 1;
        fdf->mouse.last_x = x;
        fdf->mouse.last_y = y;
    }
    else if (button == 4)  // Scroll up
    {
        fdf->camera->zoom += 2;
        redraw(fdf);
    }
    else if (button == 5)  // Scroll down
    {
        if (fdf->camera->zoom > 2)
            fdf->camera->zoom -= 2;
        redraw(fdf);
    }
    return (0);
}

// Handler for button release
int handle_mouse_release(int button, int x, int y, t_fdf *fdf)
{
    (void)x;
    (void)y;
    if (button == 1)
        fdf->mouse.left_button_down = 0;
    else if (button == 2)
        fdf->mouse.right_button_down = 0;
    return (0);
}

// Motion handler checks the state
int handle_mouse_motion(int x, int y, t_fdf *fdf)
{
    int delta_x;
    int delta_y;

    // Handle left button - PAN/MOVE
    if (fdf->mouse.left_button_down)
    {
        delta_x = x - fdf->mouse.last_x;
        delta_y = y - fdf->mouse.last_y;

        // Move the camera offsets
        fdf->camera->x_offset += delta_x;
        fdf->camera->y_offset += delta_y;

        fdf->mouse.last_x = x;
        fdf->mouse.last_y = y;

        redraw(fdf);
        return (0);
    }

    // Handle right button - ROTATE
    if (fdf->mouse.right_button_down)
    {
        delta_x = x - fdf->mouse.last_x;
        delta_y = y - fdf->mouse.last_y;

        fdf->camera->beta += delta_x * 0.01;
        fdf->camera->alpha += delta_y * 0.01;

        fdf->mouse.last_x = x;
        fdf->mouse.last_y = y;

        redraw(fdf);
        return (0);
    }

    return (0);
}
