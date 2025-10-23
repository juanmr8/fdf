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
