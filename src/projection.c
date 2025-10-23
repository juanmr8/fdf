#include "../fdf.h"

t_point isometric_projection(float x, float y, t_fdf *fdf)
{
	t_point	result;
	int		z;
	float	iso_x;
	float	iso_y;

	z = fdf->map->z_matrix[(int)y][(int)x];

	// Apply isometric projection formulas
	iso_x = ((x - y) * cos(0.523599));
	iso_y = ((x + y) * sin(0.523599) - z);

	// Apply zoom
	iso_x = iso_x * DEFAULT_ZOOM;
	iso_y = iso_y * DEFAULT_ZOOM;

	// Apply offsets
	result.x = (int)(iso_x + (WINDOW_WIDTH / 2));
	result.y = (int)(iso_y + (WINDOW_HEIGHT / 2));
	result.z = z;
	return result;
}
