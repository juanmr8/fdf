/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:00 by your_username    #+#    #+#             */
/*   Updated: 2025/01/15 12:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ================================ INCLUDES ================================ */
# include "lib/libft/libft.h"
# include "lib/get_next_line/get_next_line.h"
# include "lib/minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

/* ================================ DEFINES ================================= */
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
# define WINDOW_TITLE "FDF - Wireframe Viewer"

/* Key codes for macOS */
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125

/* Mouse codes */
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 2
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/* Colors */
# define COLOR_WHITE 0xFFFFFF

/* Default values */
# define DEFAULT_ZOOM 1
# define DEFAULT_Z_SCALE 1

/* ================================ STRUCTURES ============================== */

/* 3D Point structure */
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	// int		color;
}	t_point;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_mouse_state
{
	int	right_button_down;
	int	left_button_down;
	int	last_x;
	int	last_y;
}	t_mouse_state;

/* Map structure to hold the 3D data */
typedef struct s_map
{
	int		width;
	int		height;
	int		**z_matrix;
	int		**color_matrix;
	int		z_min;
	int		z_max;
	int		z_range;
}	t_map;

/* Map structure to draw lines */
typedef struct s_line
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
}   t_line;

/* Camera/View structure for transformations */
typedef struct s_camera
{
	int		zoom;
	int		x_offset;
	int		y_offset;
	int		z_scale;
	double	alpha;		// rotation around x-axis
	double	beta;		// rotation around y-axis
	double	gamma;		// rotation around z-axis
	int		projection;	// 0 = isometric, 1 = parallel, etc.
}	t_camera;

/* MiniLibX structure */
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

/* Main FDF structure */
typedef struct s_fdf
{
	t_map			*map;
	t_camera		*camera;
	t_mlx			*mlx;
	t_mouse_state	mouse;
}	t_fdf;

/* ================================ PROTOTYPES ============================== */

/* Map parsing functions */
int		parse_map_data(char *filename, t_map *map);
int		validate_map(t_map *map);
void	calculate_map_stats(t_map *map);

/* Map utilities */
int		get_map_dimensions(char *filename, int *width, int *height);
int		count_words(char *str, char delimiter);
int		get_color_from_string(char *str);

/* Graphics initialization */
int		init_graphics(t_fdf *fdf);
void	init_camera(t_camera *camera, t_map *map);
int		create_window(t_mlx *mlx);
int		create_image(t_mlx *mlx);

/* Drawing functions */
void	draw_map(t_fdf *fdf);
void	draw_line(t_point start, t_point end, t_fdf *fdf, int color);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	draw_horizontal_lines(t_fdf *fdf, int x, int y);
void	draw_vertical_lines(t_fdf *fdf, int x, int y);
int		get_gradient_color(int z, t_map *map);
int		get_gradient_one(double percent);
int		get_gradient_two(double percent);
int		get_gradient_three(double percent);
int		get_gradient_four(double percent);
void 	redraw(t_fdf *fdf);
t_line 	init_line(t_point start, t_point end);
void ft_write_guide(t_fdf *fdf);


/* Projection functions */
t_point	project_point(int x, int y, int z, t_fdf *fdf);
t_point	isometric_projection(float x, float y, t_fdf *fdf);
void	apply_zoom_and_offset(t_point *point, t_camera *camera);

/* Event handling */
int		handle_keypress(int keycode, t_fdf *fdf);
int		handle_mouse(int button, int x, int y, t_fdf *fdf);
int		handle_close(t_fdf *fdf);
int 	handle_mouse(int button, int x, int y, t_fdf *fdf);

/* Mouse Events */
int handle_mouse_button(int button, int x, int y, t_fdf *fdf);
int handle_mouse_release(int button, int x, int y, t_fdf *fdf);
int handle_mouse_motion(int x, int y, t_fdf *fdf);


/* Memory management */
int		allocate_map(t_map *map);
void	free_map(t_map *map);
void	free_fdf(t_fdf *fdf);
void	cleanup_and_exit(t_fdf *fdf, int exit_code);

/* Utility functions */
void	error_exit(char *message);
void	usage(void);
int		is_valid_file(char *filename);
int		ft_abs(int n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

#endif
