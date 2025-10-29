#include "../fdf.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WINDOW_WIDTH)
		return ;
	if (y < 0 || y > WINDOW_HEIGHT)
		return ;

	// mlx->img_data : A pointer to the first byte of the image buffer (memory address of pixel 0,0).

	// y * mlx->size_line : *What it calculates:** How many bytes to skip to reach the correct **row**.
	/** Example
	 *
		- You want pixel at y=3
		- Each row is 4800 bytes (`size_line`)
		- To reach row 3: skip 3 complete rows = `3 × 4800 = 14,400 bytes`

		**Visual:**
		```
		[Row 0: 4800 bytes]
		[Row 1: 4800 bytes]
		[Row 2: 4800 bytes]
		[Row 3: 4800 bytes] ← You're here after skipping 14,400 bytes

	 */

	 //  x * (mlx->bpp / 8): **What it calculates:** How many bytes to skip **within the row** to reach the correct column.
	/**	 * Example
		* **What it calculates:** How many bytes to skip **within the row** to reach the correct column.

	**Breaking it down:**
	- `mlx->bpp` = bits per pixel = 32
	- `mlx->bpp / 8` = bytes per pixel = 32/8 = 4
	- `x * 4` = how many bytes to skip for x pixels

	**Example:**
	- You want pixel at x=5
	- Each pixel is 4 bytes
	- To reach column 5: skip 5 pixels = `5 × 4 = 20 bytes`

	**Visual (zoomed into Row 3):**
	```
	Row 3: [P0][P1][P2][P3][P4][P5][P6]...
		↑4b ↑4b ↑4b ↑4b ↑4b ↑4b
		Skip 20 bytes to reach P5 ───────┘
	 */
	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));

	/**
	 * **What it does:** Converts `dst` from `char *` to `unsigned int *`
	**Why?**
	- `dst` is `char *` (1-byte pointer)
	- Colors are 4 bytes (32 bits = `unsigned int`)
	- We need to write 4 bytes at once, not 1 byte!

	**Visual:**
	```
	Before cast:
	dst → [1 byte]

	After cast to (unsigned int*):
	dst → [4 bytes as one unit]
	 */
	*(unsigned int*)dst = color;
}

void	draw_line(t_point start, t_point end, t_fdf *fdf)
{
	t_line	line;
	int	x;
	int	y;
	int	e2;

	line = init_line(start, end);
	x = start.x;
	y = start.y;

	while(1)
	{
		put_pixel(fdf->mlx, x, y, COLOR_WHITE);
		if (x == end.x && y == end.y)
			break ;
		e2 = line.err * 2;
		if (e2 > -line.dy)
		{
			line.err -= line.dy;
			x += line.sx;
		}
		if (e2 < line.dx)
		{
			line.err += line.dx;
			y += line.sy;
		}
	}
}

void draw_map(t_fdf *fdf)
{
	int	x; // Loop through cols
	int	y; // Loop through rows
	t_point current; // Screen coordinates of current point
	t_point right; // Screen coordinates of right neighbor
	t_point down; // Screen coordinates of down neighbor

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
			{
				current = isometric_projection(x, y, fdf);
				right = isometric_projection(x + 1, y, fdf);
				draw_line(current, right, fdf);
			}
			if (y < fdf->map->height - 1)
			{
				current = isometric_projection(x, y, fdf);
				down = isometric_projection(x, y + 1, fdf);
				draw_line(current, down, fdf);
			}
			x++;
		}
		y++;
	}
}

t_line init_line(t_point start, t_point end)
{
	t_line line;

	line.dx = abs(end.x - start.x);
	line.dy = abs(end.y - start.y);
	line.sx = (start.x < end.x) ? 1 : -1;
	line.sy = (start.y < end.y) ? 1 : -1;
	line.err = line.dx - line.dy;

	return (line);
}

