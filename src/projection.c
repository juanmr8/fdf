#include "../fdf.h"

// t_point isometric_projection(float x, float y, t_fdf *fdf)
// {
// 	t_point	result;
// 	int		z;
// 	float	iso_x;
// 	float	iso_y;

// 	z = fdf->map->z_matrix[(int)y][(int)x];

// 	// Apply isometric projection formulas
// 	iso_x = ((x - y) * cos(0.523599));
// 	iso_y = ((x + y) * sin(0.523599) - z);

// 	// Apply zoom
// 	iso_x = iso_x * fdf->camera->zoom;
// 	iso_y = iso_y * fdf->camera->zoom;

// 	// Apply offsets
// 	result.x = (int)(iso_x + (WINDOW_WIDTH / 2));
// 	result.y = (int)(iso_y + (WINDOW_HEIGHT / 2));
// 	result.z = z;
// 	return result;
// }

t_point isometric_projection(float x, float y, t_fdf *fdf)
{
	t_point	result;
	float	z;
	float	x_rot, y_rot, z_rot;
	float	iso_x, iso_y;

	z = fdf->map->z_matrix[(int)y][(int)x];

	// Center coordinates for rotation (translate to the center from left corner)
	/** EXPLANATION
	 * Original coordinates:       After centering:
		(0,0) (1,0) (2,0) (3,0)    (-2,-2) (-1,-2) (0,-2) (1,-2)
		(0,1) (1,1) (2,1) (3,1)    (-2,-1) (-1,-1) (0,-1) (1,-1)
		(0,2) (1,2) (2,2) (3,2)    (-2, 0) (-1, 0) (0, 0) (1, 0)
		(0,3) (1,3) (2,3) (3,3)    (-2, 1) (-1, 1) (0, 1) (1, 1)
		Center: (2.0, 2.0)         Center: (0, 0) ← Now at origin!
	 */
	x = x - fdf->map->width / 2.0;
	y = y - fdf->map->height / 2.0;

	// Rotation around X-axis (alpha)
	y_rot = y * cos(fdf->camera->alpha) - z * sin(fdf->camera->alpha);
	z_rot = y * sin(fdf->camera->alpha) + z * cos(fdf->camera->alpha);
	y = y_rot;
	z = z_rot;

	// Rotation around Y-axis (beta)
	x_rot = x * cos(fdf->camera->beta) + z * sin(fdf->camera->beta);
	z_rot = -x * sin(fdf->camera->beta) + z * cos(fdf->camera->beta);
	x = x_rot;
	z = z_rot;

	// Apply isometric projection
	iso_x = (x - y) * cos(0.523599);
	iso_y = (x + y) * sin(0.523599) - z;

	// Apply zoom
	iso_x = iso_x * fdf->camera->zoom;
	iso_y = iso_y * fdf->camera->zoom;

	// Apply offsets
	result.x = (int)(iso_x + fdf->camera->x_offset);
	result.y = (int)(iso_y + fdf->camera->y_offset);
	result.z = (int)z;

	return result;
}
