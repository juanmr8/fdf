/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:58:39 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/11/12 11:32:23 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ================================ INCLUDES ================================ */
# include "lib/libft/libft.h"
# include "lib/get_next_line/get_next_line.h"
# include "lib/ft_printf/ft_printf.h"
# include "lib/minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define WINDOW_TITLE "FDF - Wireframe Viewer"

# define KEY_ESC 65307
# define KEY_SPACE 32
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define KEY_5 53
# define CLICK_RIGHT 3

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}	t_point;

typedef struct s_mouse_state
{
	int	right_button_down;
	int	left_button_down;
	int	last_x;
	int	last_y;
}	t_mouse_state;

typedef struct s_map
{
	int		width;
	int		height;
	int		**z_matrix;
	int		z_min;
	int		z_max;
	int		z_range;
}	t_map;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_camera
{
	int		zoom;
	int		x_offset;
	int		y_offset;
	double	alpha;
	double	beta;
	int		color_scheme;
}	t_camera;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		screen_width;
	int		screen_height;
}	t_mlx;

typedef struct s_fdf
{
	t_map			*map;
	t_camera		*camera;
	t_mlx			*mlx;
	t_mouse_state	mouse;
}	t_fdf;

int		parse_map_data(char *filename, t_map *map);
void	calculate_map_stats(t_map *map);
int		get_map_dimensions(char *filename, int *width, int *height);
int		count_words(char *str, char delimiter);
int		init_graphics(t_fdf *fdf);
void	draw_map(t_fdf *fdf);
void	draw_line(t_point start, t_point end, t_fdf *fdf, int color);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	draw_horizontal_lines(t_fdf *fdf, int x, int y);
void	draw_vertical_lines(t_fdf *fdf, int x, int y);
int		get_gradient_color(int z, t_map *map, t_fdf *fdf);
int		get_gradient_one(double percent);
int		get_gradient_two(double percent);
int		get_gradient_three(double percent);
int		get_gradient_four(double percent);
void	redraw(t_fdf *fdf);
t_line	init_line(t_point start, t_point end);
void	init_hooks(t_fdf *fdf);
void	ft_write_guide(t_fdf *fdf);
t_point	isometric_projection(float x, float y, t_fdf *fdf);
int		handle_keypress(int keycode, t_fdf *fdf);
void	handle_zoom_and_reset(int keycode, t_fdf *fdf);
int		handle_color_keys(int keycode, t_fdf *fdf);
void	handle_key_number(int scheme, t_fdf *fdf);
int		handle_mouse(int button, int x, int y, t_fdf *fdf);
int		handle_close(t_fdf *fdf);
int		handle_mouse_button(int button, int x, int y, t_fdf *fdf);
int		handle_mouse_release(int button, int x, int y, t_fdf *fdf);
int		handle_mouse_motion(int x, int y, t_fdf *fdf);
int		allocate_map(t_map *map);
void	error_exit(char *message);
void	usage(void);
int		is_valid_file(char *filename);
void	free_map(t_map *map);
void	free_resources(t_fdf *fdf);

#endif
