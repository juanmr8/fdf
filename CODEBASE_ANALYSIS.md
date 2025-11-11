# FDF (Fil de Fer) - Complete Codebase Analysis

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Data Structures](#data-structures)
4. [Execution Flow](#execution-flow)
5. [Module Breakdown](#module-breakdown)
6. [Key Algorithms](#key-algorithms)
7. [Event System](#event-system)
8. [Memory Management](#memory-management)
9. [Build System](#build-system)
10. [Current Issues](#current-issues)

---

## Project Overview

**FDF (Fil de Fer)** is a 3D wireframe visualization program that renders heightmap data files (.fdf format). It's part of the 42 school curriculum and demonstrates:
- File parsing and validation
- 3D graphics projection (isometric)
- Interactive user controls (mouse + keyboard)
- Real-time rendering with MiniLibX
- Memory management in C

### Key Features
- **Interactive Rotation**: Right-click + drag to rotate around X and Y axes
- **Panning**: Left-click + drag to move the view
- **Zoom Control**: Mouse wheel or +/- keys
- **Color Schemes**: 5 different gradient color schemes (keys 1-5)
- **Reset View**: Spacebar resets camera to initial position

---

## Architecture

### High-Level Design Pattern

The project follows a **modular, event-driven architecture** with clear separation of concerns:

```
┌─────────────────────────────────────────────┐
│           Entry Point (fdf.c)                │
│  - Initialization orchestration              │
│  - Main event loop                           │
└──────────────┬──────────────────────────────┘
               │
       ┌───────┴───────┐
       │               │
   ┌───▼────┐    ┌────▼────┐
   │  Data  │    │ Graphics│
   │ Layer  │    │  Layer  │
   └───┬────┘    └────┬────┘
       │              │
   ┌───▼──────────────▼────┐
   │   Event Handlers       │
   │ (Keyboard/Mouse)       │
   └────────────────────────┘
```

### Directory Structure

```
fdf/
├── fdf.c                 # Entry point
├── fdf.h                 # All type definitions and function declarations
├── src/                  # Modular implementation
│   ├── map_parsing.c     # File I/O and parsing
│   ├── map_utils.c       # Map dimension and statistics
│   ├── graphics_init.c   # MiniLibX initialization
│   ├── drawing.c         # Core rendering logic
│   ├── drawing_utils.c   # Line drawing helpers
│   ├── projection.c      # 3D transformations
│   ├── color.c           # Color gradient calculations
│   ├── events.c          # Event hook setup
│   ├── keyboard.c        # Keyboard handlers
│   ├── mouse.c           # Mouse handlers
│   ├── memory.c          # Allocation and cleanup
│   └── error.c           # Error handling
└── lib/                  # External libraries
    ├── libft/            # Custom C library
    ├── get_next_line/    # Line-by-line file reading
    ├── ft_printf/        # Custom printf
    └── minilibx/         # Graphics library
```

---

## Data Structures

### Core Structures (defined in fdf.h)

#### 1. `t_point` - 3D Point Representation
```c
typedef struct s_point {
    int x;  // Screen X coordinate (after projection)
    int y;  // Screen Y coordinate (after projection)
    int z;  // Z value from heightmap
} t_point;
```
**Purpose**: Represents a point in 3D space and its 2D screen projection.

#### 2. `t_map` - Heightmap Data
```c
typedef struct s_map {
    int     width;          // Number of columns
    int     height;         // Number of rows
    int     **z_matrix;     // 2D array of height values
    int     **color_matrix; // 2D array of colors (currently unused)
    int     z_min;          // Minimum height in map
    int     z_max;          // Maximum height in map
    int     z_range;        // z_max - z_min
} t_map;
```
**Purpose**: Stores the parsed heightmap data and statistics for rendering.

**Note**: `color_matrix` is allocated but never populated - potential area for enhancement.

#### 3. `t_camera` - View Parameters
```c
typedef struct s_camera {
    int     zoom;           // Zoom factor (default: 20)
    int     x_offset;       // Pan X (default: WINDOW_WIDTH/2)
    int     y_offset;       // Pan Y (default: WINDOW_HEIGHT/2)
    int     z_scale;        // Z-axis scaling (currently unused)
    double  alpha;          // Rotation around X-axis
    double  beta;           // Rotation around Y-axis
    double  gamma;          // Rotation around Z-axis (unused)
    int     projection;     // Projection type (unused, always isometric)
    int     color_scheme;   // Color gradient selector (0-4)
} t_camera;
```
**Purpose**: Controls how the 3D scene is viewed and rendered.

#### 4. `t_mlx` - Graphics Context
```c
typedef struct s_mlx {
    void    *mlx_ptr;   // MiniLibX connection
    void    *win_ptr;   // Window pointer
    void    *img_ptr;   // Image buffer pointer
    char    *img_data;  // Direct pixel data access
    int     bpp;        // Bits per pixel
    int     size_line;  // Bytes per line
    int     endian;     // Endianness
} t_mlx;
```
**Purpose**: Encapsulates all MiniLibX-related data for graphics operations.

#### 5. `t_mouse_state` - Mouse Tracking
```c
typedef struct s_mouse_state {
    int right_button_down;  // Right button pressed flag
    int left_button_down;   // Left button pressed flag
    int last_x;             // Last mouse X position
    int last_y;             // Last mouse Y position
} t_mouse_state;
```
**Purpose**: Tracks mouse button states and position for drag operations.

#### 6. `t_fdf` - Main Program Context
```c
typedef struct s_fdf {
    t_map           *map;     // Pointer to map data
    t_camera        *camera;  // Pointer to camera settings
    t_mlx           *mlx;     // Pointer to graphics context
    t_mouse_state   mouse;    // Mouse state (value, not pointer)
} t_fdf;
```
**Purpose**: Central data structure that ties everything together. Passed to all event handlers.

#### 7. `t_line` - Bresenham Line Algorithm Data
```c
typedef struct s_line {
    int dx;   // Delta X
    int dy;   // Delta Y
    int sx;   // Step direction X (-1 or 1)
    int sy;   // Step direction Y (-1 or 1)
    int err;  // Error accumulator
} t_line;
```
**Purpose**: Stores intermediate data for efficient line drawing.

---

## Execution Flow

### Program Lifecycle

```
main()
  │
  ├─► init_map()           	  ─┐
  │   ├─ get_map_dimensions()  │  PHASE 1: Data Loading
  │   ├─ allocate_map()        │
  │   ├─ parse_map_data()      │
  │   └─ calculate_map_stats() ┘
  │
  ├─► init_camera()        ─── PHASE 2: Setup
  │
  ├─► init_fdf()           ─── PHASE 3: Context Creation
  │
  ├─► init_graphics()      ─┐
  │   ├─ mlx_init()            │  PHASE 4: Graphics Init
  │   ├─ mlx_new_window()      │
  │   └─ mlx_new_image()      ┘
  │
  ├─► first_paint()        ─┐
  │   ├─ draw_map()            │  PHASE 5: Initial Render
  │   └─ ft_write_guide()     ┘
  │
  ├─► init_hooks()         ─── PHASE 6: Event Setup
  │
  └─► mlx_loop()           ─── PHASE 7: Event Loop (runs until exit)
```

### Detailed Phase Breakdown

#### Phase 1: Map Loading (init_map)
1. **get_map_dimensions()**: Opens file twice
   - First pass: Count lines (height) and words per line (width)
   - Uses `get_next_line()` for line-by-line reading
   - Takes maximum word count as width (handles irregular maps)

2. **allocate_map()**: Dynamic memory allocation
   - Allocates array of pointers for height
   - For each row, allocates array of ints for width
   - Handles allocation failures by freeing partial allocations

3. **parse_map_data()**: Populates the z_matrix
   - Opens file again
   - Uses `ft_split()` to tokenize each line
   - Converts string numbers to integers with `ft_atoi()`
   - Frees temporary string arrays after each line

4. **calculate_map_stats()**: Computes statistics
   - Finds z_min and z_max by iterating entire matrix
   - Calculates z_range for color gradient normalization

#### Phase 2-3: Initialization
- `init_camera()`: Sets default view parameters
  - Centered view (WINDOW_WIDTH/2, WINDOW_HEIGHT/2)
  - Default zoom: 20
  - No initial rotation (alpha, beta = 0.0)
  - First color scheme (0)

- `init_fdf()`: Links all components together
  - Connects map, camera, and mlx structures
  - Initializes mouse state to "released"

#### Phase 4: Graphics Initialization
```c
mlx_init()           // Connect to X server
mlx_new_window()     // Create 1200x800 window
mlx_do_sync()        // Synchronize with X server (Linux specific)
mlx_new_image()      // Create image buffer
mlx_get_data_addr()  // Get direct pixel access
```

#### Phase 5: First Paint
- **draw_map()**: Renders entire wireframe
  - Iterates through all grid points
  - Draws horizontal line (to point on right)
  - Draws vertical line (to point below)
  - Each line colored based on source point's z value

- **mlx_put_image_to_window()**: Display buffer to screen

- **ft_write_guide()**: Overlays control instructions

#### Phase 6: Event Hook Registration
```c
mlx_hook(win_ptr, 2,  ..., handle_keypress,      fdf);  // Key press
mlx_hook(win_ptr, 17, ..., handle_close,         fdf);  // Window close
mlx_hook(win_ptr, 4,  ..., handle_mouse_button,  fdf);  // Mouse down
mlx_hook(win_ptr, 5,  ..., handle_mouse_release, fdf);  // Mouse up
mlx_hook(win_ptr, 6,  ..., handle_mouse_motion,  fdf);  // Mouse move
```

#### Phase 7: Event Loop
- `mlx_loop()` blocks and waits for events
- Calls registered handlers when events occur
- Continues until program exit (ESC key or window close)

---

## Module Breakdown

### 1. Map Parsing Module (map_parsing.c, map_utils.c)

**Responsibility**: File I/O and data extraction

#### Key Functions:

**`get_map_dimensions(filename, *width, *height)`**
- **Algorithm**:
  1. Open file
  2. Read line-by-line with `get_next_line()`
  3. Count words per line with `count_words(line, ' ')`
  4. Track maximum word count as width
  5. Track line count as height
- **Return**: 1 on success, 0 on failure
- **Why it works this way**: Determines matrix size before allocation

**`parse_map_data(filename, map)`**
- **Algorithm**:
  1. Open file again
  2. For each line:
     - Split by space with `ft_split()`
     - Parse each token to int with `ft_atoi()`
     - Store in `map->z_matrix[y][x]`
     - Free temporary string array
- **Memory Safety**: Properly frees all temporary allocations
- **Limitation**: Doesn't parse hexadecimal colors (e.g., "10,0xFF0000")

**`calculate_map_stats(map)`**
- **Purpose**: Finds min/max z values for gradient calculation
- **Complexity**: O(width × height)
- **Used by**: Color gradient system to normalize percentages

**`count_words(str, delimiter)`**
- **Purpose**: Helper to count space-separated integers
- **Handles**: Multiple consecutive spaces and newline characters
- **Edge Case**: Treats '\n' as word terminator

---

### 2. Graphics Initialization (graphics_init.c)

**Responsibility**: MiniLibX setup and window creation

**`init_graphics(fdf)`**
```c
// Initialization sequence:
1. mlx_init()              → Initialize connection to display
2. mlx_new_window()        → Create 1200x800 window
3. mlx_do_sync()           → Sync with X server (Linux only)
4. mlx_new_image()         → Create off-screen buffer
5. mlx_get_data_addr()     → Get pointer for direct pixel manipulation
```

**Purpose of Off-Screen Rendering**:
- All drawing happens to `img_data` buffer first
- Complete frame assembled before display
- Prevents flickering (double buffering)
- Only one `mlx_put_image_to_window()` call per frame

---

### 3. Projection Module (projection.c)

**Responsibility**: 3D to 2D coordinate transformation

#### Mathematical Pipeline:

```
Original Grid Point (x, y, z_matrix[y][x])
           ↓
1. Center the point
   x' = x - width/2
   y' = y - height/2
           ↓
2. Apply X-axis rotation (alpha)
   y_rot = y' * cos(α) - z * sin(α)
   z_rot = y' * sin(α) + z * cos(α)
           ↓
3. Apply Y-axis rotation (beta)
   x_rot = x' * cos(β) + z_rot * sin(β)
   z_rot = -x' * sin(β) + z_rot * cos(β)
           ↓
4. Isometric projection
   iso_x = (x_rot - y_rot) * cos(30°)
   iso_y = (x_rot + y_rot) * sin(30°) - z_rot
           ↓
5. Scale and translate to screen
   screen_x = iso_x * zoom + x_offset
   screen_y = iso_y * zoom + y_offset
```

**Key Constant**: `0.523599` = 30° in radians
- This creates the classic isometric view (30° angle)

**Why this order matters**:
1. Centering: Makes rotations happen around object center
2. Rotations before projection: More intuitive control
3. Projection after rotation: Maintains 3D relationships
4. Scale last: Independent of other transformations

**Functions**:
- `rotate_around_x()`: Pitch rotation
- `rotate_around_y()`: Yaw rotation
- `to_isometric()`: Final 2D projection
- `isometric_projection()`: Main pipeline function

---

### 4. Drawing Module (drawing.c, drawing_utils.c)

**Responsibility**: Rendering the wireframe

#### Core Rendering Loop:

```c
draw_map(fdf):
    for y in 0..height:
        for x in 0..width:
            if (x < width-1):  // Not last column
                draw_horizontal_lines(x, y)
            if (y < height-1):  // Not last row
                draw_vertical_lines(x, y)
```

**Why this works**:
- Each point connects to its right neighbor and down neighbor
- Creates complete mesh without duplicate lines
- Edge points naturally don't connect beyond bounds

#### Line Drawing: Bresenham's Algorithm

**`draw_line(start, end, fdf, color)`**
```c
Algorithm:
1. Calculate dx, dy (absolute differences)
2. Determine step direction (sx, sy): -1 or +1
3. Initialize error term: err = dx - dy
4. Loop until reaching end point:
   - Draw pixel at current position
   - Update error term
   - Step in X if error > -dy
   - Step in Y if error < dx
```

**Why Bresenham**:
- Integer-only arithmetic (fast)
- No floating-point calculations
- Produces smooth, connected lines
- Industry standard for rasterization

**`put_pixel(mlx, x, y, color)`**
- Direct memory access for speed
- Bounds checking prevents segfaults
- Calculates pixel address: `base + (y * line_size + x * bpp/8)`
- Uses `mlx_get_color_value()` for color encoding

**`redraw(fdf)`**
```c
1. ft_bzero(img_data, total_bytes)  // Clear buffer (fill with black)
2. draw_map(fdf)                     // Render wireframe
3. mlx_put_image_to_window()         // Display to screen
4. ft_write_guide(fdf)               // Overlay text instructions
```

---

### 5. Color Module (color.c)

**Responsibility**: Dynamic color gradient generation

#### Color System Architecture:

**`get_gradient_color(z, map, fdf)`**
1. Calculate normalized percentage: `(z - z_min) / z_range`
2. Select gradient function based on `color_scheme`
3. Return interpolated RGB color

**Four Gradient Schemes**:

**Scheme 0** (Default - Warm/Earth):
- 0.00-0.14: `0xF45B69` (Red-pink)
- 0.14-0.28: `0xF06B6F` (Coral)
- 0.28-0.42: `0xEC7B75` (Light coral)
- 0.42-0.56: `0xE88B7B` (Peach)
- 0.56-0.70: `0xE49B81` (Tan)
- 0.70-0.84: `0xE0AB87` (Beige)
- 0.84-1.00: `0xE4FDE1` (Pale green)

**Scheme 1** (Ocean Blues):
- 0.00-0.14: `0x000080` (Navy)
- → Progressive lightening →
- 0.84-1.00: `0xAFEEEE` (Pale turquoise)

**Scheme 2** (Forest Greens):
- 0.00-0.14: `0x013220` (Dark green)
- → Progressive lightening →
- 0.84-1.00: `0xF0FFF0` (Honeydew)

**Scheme 3** (Purple/Pink):
- 0.00-0.14: `0x4B0082` (Indigo)
- → Progressive lightening →
- 0.84-1.00: `0xFFF0F5` (Lavender blush)

**Design Pattern**: Step-wise linear interpolation
- 7 color stops per gradient
- ~14% range per stop
- Simple, fast lookup (no complex interpolation)

---

### 6. Event System (events.c, keyboard.c, mouse.c)

**Responsibility**: User interaction handling

#### Event Hook Mapping:

| X11 Event | Code | Handler | Purpose |
|-----------|------|---------|---------|
| KeyPress | 2 | `handle_keypress` | Keyboard input |
| DestroyNotify | 17 | `handle_close` | Window close button |
| ButtonPress | 4 | `handle_mouse_button` | Mouse click down |
| ButtonRelease | 5 | `handle_mouse_release` | Mouse click up |
| MotionNotify | 6 | `handle_mouse_motion` | Mouse movement |

#### Keyboard Controls:

**`handle_keypress(keycode, fdf)`**
```c
KEY_ESC (65307)  → free_resources() + exit(0)
KEY_PLUS (61)    → zoom += 2, redraw()
KEY_MINUS (45)   → zoom -= 2 (min: 2), redraw()
KEY_SPACE (32)   → reset_camera(), redraw()
KEY_1 (49)       → color_scheme = 0, redraw()
KEY_2 (50)       → color_scheme = 1, redraw()
KEY_3 (51)       → color_scheme = 2, redraw()
KEY_4 (52)       → color_scheme = 3, redraw()
KEY_5 (53)       → color_scheme = 4, redraw()
```

**`reset_camera(fdf)`**
- alpha, beta = 0.0 (no rotation)
- zoom = 20 (default)
- Offset to window center

#### Mouse Controls:

**Button Mapping**:
- Button 1: Left click (pan/drag)
- Button 3: Right click (rotate)
- Button 4: Scroll up (zoom in)
- Button 5: Scroll down (zoom out)

**`handle_mouse_button(button, x, y, fdf)`**
```c
Button 1 → left_button_down = 1, store (x, y)
Button 3 → right_button_down = 1, store (x, y)
Button 4 → zoom += 2, redraw()
Button 5 → zoom -= 2, redraw()
```

**`handle_mouse_motion(x, y, fdf)`**
```c
if (left_button_down):
    delta_x = x - last_x
    delta_y = y - last_y
    x_offset += delta_x
    y_offset += delta_y
    update last_x, last_y
    redraw()

if (right_button_down):
    delta_x = x - last_x
    delta_y = y - last_y
    beta += delta_x * 0.01   // Horizontal drag → Y-axis rotation
    alpha += delta_y * 0.01  // Vertical drag → X-axis rotation
    update last_x, last_y
    redraw()
```

**Motion Sensitivity**: `0.01` radians per pixel
- 100 pixels drag ≈ 1 radian ≈ 57.3°
- Smooth, controllable rotation

---

### 7. Memory Management (memory.c)

**Responsibility**: Allocation and cleanup

#### Allocation Strategy:

**`allocate_map(map)`**
```c
Algorithm:
1. Allocate array of height pointers (rows)
2. For each row i (0 to height-1):
   a. Allocate width integers (columns)
   b. If allocation fails:
      - Free all previously allocated rows (0 to i-1)
      - Free row pointer array
      - Return 0 (failure)
   c. Assign pointer to z_matrix[i]
3. Return 1 (success)
```

**Failure Safety**: Partial allocation rollback prevents leaks

#### Cleanup Strategy:

**`free_map(map)`**
- Null checks before freeing
- Iterates through all allocated rows
- Frees rows before row array
- Nullifies pointers after freeing (defensive)

**`free_resources(fdf)`**
```c
Cleanup Order:
1. mlx_destroy_image(img_ptr)
2. mlx_destroy_window(win_ptr)
3. mlx_destroy_display(mlx_ptr)
4. free(mlx_ptr)
5. free_map(map)
```

**Critical**: MiniLibX resources must be freed before `mlx_ptr` itself

#### File Validation:

**`is_valid_file(filename)`**
- Attempts to open file in read-only mode
- Closes immediately (doesn't read)
- Returns success/failure boolean
- Called before processing to fail fast

---

### 8. Error Handling (error.c)

**Responsibility**: User-facing error messages

**`error_exit(message)`**
- Prints: `"Error: <message>\n"`
- Exits with status code 1
- Used throughout for fatal errors

**`usage()`**
- Prints: `"Usage: fdf <filename.fdf>\n"`
- Called when argc != 2
- Doesn't exit (allows manual exit)

**Error Points in Execution**:
1. `argc != 2` → usage()
2. File can't be opened → "Cannot read file"
3. `get_map_dimensions()` fails → "Failed to get dimensions"
4. `allocate_map()` fails → "Failed to allocate memory"
5. `parse_map_data()` fails → "Failed to parse map data"
6. `init_graphics()` fails → "Failed to initialize graphics"

**Limitation**: No error recovery - all errors are fatal

---

## Key Algorithms

### 1. Bresenham's Line Algorithm

**Purpose**: Draw straight line between two points using only integers

**Why it's used**:
- Extremely fast (no division, multiplication, or floating point)
- Produces visually smooth lines
- Memory efficient
- Works for all angles

**Implementation in draw_line()**:
```c
dx = |x2 - x1|
dy = |y2 - y1|
sx = (x1 < x2) ? 1 : -1  // X step direction
sy = (y1 < y2) ? 1 : -1  // Y step direction
err = dx - dy             // Error accumulator

while (true):
    plot(x, y)
    if (x == x2 && y == y2):
        break

    e2 = err * 2
    if (e2 > -dy):        // Error too positive
        err -= dy
        x += sx
    if (e2 < dx):         // Error too negative
        err += dx
        y += sy
```

**How it decides when to step**:
- Tracks cumulative error between ideal and drawn line
- Steps in dominant axis always
- Steps in secondary axis when error exceeds threshold
- Results in minimal deviation from true line

### 2. Isometric Projection

**Purpose**: Convert 3D coordinates to 2D screen space with depth perception

**Mathematical Foundation**:
```
Standard isometric projection:
- View angle: 30° from horizontal
- All axes equally foreshortened
- No perspective (parallel projection)

Projection equations:
screen_x = (x - y) * cos(30°)
screen_y = (x + y) * sin(30°) - z

Where:
cos(30°) ≈ 0.866
sin(30°) = 0.5
```

**Advantages of isometric**:
- Maintains parallel lines (no perspective distortion)
- Equal scaling on all axes
- Easy to mentally reconstruct 3D from 2D
- Standard in technical drawings and games

### 3. Color Gradient Mapping

**Purpose**: Visually represent height data through color

**Algorithm**:
```c
normalize(z) = (z - z_min) / (z_max - z_min)  // Returns 0.0 to 1.0

map_to_gradient(percentage):
    if (percentage < 0.14): return COLOR_0
    else if (percentage < 0.28): return COLOR_1
    else if (percentage < 0.42): return COLOR_2
    // ... etc
```

**Why 7 steps**:
- Balance between smoothness and simplicity
- ~14% per step visible to human eye
- Avoids costly real-time interpolation
- Sufficient for most visualizations

### 4. 3D Rotation Matrices

**X-Axis Rotation (Pitch)**:
```
[ 1    0         0    ] [ x ]   [ x ]
[ 0  cos(α)  -sin(α) ] [ y ] = [ y' ]
[ 0  sin(α)   cos(α) ] [ z ]   [ z' ]

Result:
y' = y * cos(α) - z * sin(α)
z' = y * sin(α) + z * cos(α)
```

**Y-Axis Rotation (Yaw)**:
```
[  cos(β)  0  sin(β) ] [ x ]   [ x' ]
[    0     1    0    ] [ y ] = [ y  ]
[ -sin(β)  0  cos(β) ] [ z ]   [ z' ]

Result:
x' = x * cos(β) + z * sin(β)
z' = -x * sin(β) + z * cos(β)
```

**Application Order**:
1. X-axis (pitch) - look up/down
2. Y-axis (yaw) - look left/right
3. Z-axis (roll) - tilt (unused in FDF)

**Why this order**: Gimbal lock prevention and intuitive control

---

## Event System Deep Dive

### MiniLibX Event Loop

**`mlx_loop(mlx_ptr)`**:
- Blocking call that waits for X11 events
- Calls registered hooks when events occur
- Continues until program termination

### Event Hook Registration

**`mlx_hook(win_ptr, event, mask, function, param)`**

Parameters:
- `win_ptr`: Window to monitor
- `event`: X11 event code (2=KeyPress, 4=ButtonPress, etc.)
- `mask`: X11 event mask (bit flags)
- `function`: Callback function
- `param`: User data passed to callback (our `t_fdf *fdf`)

### Redraw Triggering

Every interactive change triggers `redraw()`:
```c
redraw(fdf):
    1. ft_bzero(img_data, buffer_size)  // Clear to black
    2. draw_map(fdf)                     // Render with new parameters
    3. mlx_put_image_to_window(...)      // Display
    4. ft_write_guide(fdf)               // Re-overlay text
```

**Performance Note**:
- Full redraw on every change (no delta rendering)
- Fast enough for interactive framerates on modern hardware
- Bottleneck: Number of lines to draw (map size × connections per point)

### Mouse State Management

**State Machine**:
```
IDLE → Button Down → DRAGGING → Button Up → IDLE
       ↑                |
       |                ↓
       └─── Motion ─────┘
          (with button down)
```

**Tracking**:
- `left_button_down` / `right_button_down`: Binary flags
- `last_x` / `last_y`: Previous position for delta calculation
- Updated on press, motion, and release events

---

## Memory Management Deep Dive

### Allocation Patterns

**Stack Allocation** (automatic cleanup):
- Main function local variables: `fdf`, `map`, `mlx`, `camera`
- Function parameters
- Local loop variables

**Heap Allocation** (manual cleanup required):
- `map->z_matrix`: 2D array (height × width integers)
- `map->color_matrix`: 2D array (currently unused)
- MiniLibX internal structures (mlx_ptr, win_ptr, img_ptr)
- Temporary strings in parsing (`get_next_line`, `ft_split`)

### Ownership Model

**Map Data**:
- Allocated in `init_map()`
- Owned by `t_map` structure
- Freed in `free_map()` (called by `free_resources()`)

**MiniLibX Resources**:
- Allocated by MiniLibX functions
- Owned by `t_mlx` structure
- Freed by MiniLibX cleanup functions

**Temporary Allocations**:
- `get_next_line()` result → freed immediately after use
- `ft_split()` result → freed after parsing line
- Local ownership, local cleanup

### Leak Prevention

**Clean Exit Points**:
1. ESC key → `handle_keypress()` → `free_resources()` → `exit(0)`
2. Window close → `handle_close()` → `free_resources()` → `exit(0)`
3. Fatal error → `error_exit()` → immediate `exit(1)` (LEAKS!)

**Known Issue**: Error exits don't call `free_resources()`
- All `error_exit()` calls leak allocated memory
- Mitigated by: OS reclaims memory on process termination
- Best practice: Should free before exiting

### Defensive Programming

**Null Checks**:
- `free_map()` checks if map is NULL
- `free_resources()` checks all pointers before freeing
- Prevents double-free and null-dereference

**Pointer Nullification**:
- After freeing, pointers set to NULL
- Prevents use-after-free bugs
- Safe for repeated calls

---

## Build System

### Makefile Structure

**Dependencies**:
```
fdf (executable)
├── fdf.c
├── src/*.c (12 source files)
├── libft.a (custom C library)
├── libftprintf.a (custom printf)
├── get_next_line.o (line reading)
└── libmlx.a (graphics library)
```

**Compilation Flags**:
- `-Wall -Wextra -Werror`: Strict warnings-as-errors
- `-g`: Debug symbols
- `-DGL_SILENCE_DEPRECATION`: Suppress OpenGL warnings
- `-lXext -lX11 -lm`: Link X11 and math libraries

**Phony Targets**:
- `all`: Build everything (default)
- `clean`: Remove object files
- `fclean`: Remove objects and executable
- `re`: Full rebuild (fclean + all)
- `test`: Build and run with `test_maps/42.fdf`
- `debug`: Build with address sanitizer
- `leaks`: Run with leak detection (macOS)

**Build Order**:
1. libft → libftprintf → get_next_line → minilibx
2. Compile all .c to .o with includes
3. Link everything into `fdf` executable

**Platform Specific**:
- Linux: Uses X11 libraries
- macOS: Would use different flags (AppKit/Cocoa)
- Current Makefile configured for Linux

---

## Current Issues and Observations

### 1. **Logic Error in main()**

**Location**: `fdf.c:75-87`
```c
map = init_map(&map, argv);       // Uses argv
camera = init_camera(&camera);
fdf = init_fdf(&fdf, &map, &mlx, &camera);

if (argc != 2) {                  // Checked AFTER using argv[1]!
    usage();
    return (1);
}
```

**Problem**: Argument count checked after `argv[1]` already dereferenced
**Impact**: Undefined behavior if argc < 2
**Fix**: Move argc check to top of main(), before any other code

### 2. **Unused Structure Members**

**t_map.color_matrix**:
- Allocated in `allocate_map()`
- Freed in `free_map()`
- Never populated or read
- Wastes memory for large maps

**t_camera.z_scale**:
- Initialized to 1
- Never modified or used in calculations
- Could be removed or implemented

**t_camera.gamma**:
- Initialized to 0.0
- Z-axis rotation not implemented
- Dead field

**t_camera.projection**:
- Initialized to 0
- Only isometric projection implemented
- No other projection modes

### 3. **Color Parsing Not Implemented**

**Expected Feature**: FDF files can specify colors like `"10,0xFF0000"`

**Current Behavior**:
- `ft_atoi("10,0xFF0000")` returns `10` only
- Color component ignored entirely
- `color_matrix` never populated

**Why it's missing**: Parsing hexadecimal colors is complex
**Impact**: All maps use gradient coloring, no custom colors

### 4. **Memory Leak on Error**

**Problem**: `error_exit()` calls `exit(1)` without cleanup

**Leak Scenarios**:
```c
if (!allocate_map(map))
    error_exit("...");  // Leaks any partially allocated memory!

if (!parse_map_data(argv[1], map))
    error_exit("...");  // Leaks map->z_matrix!

if (!init_graphics(&fdf))
    error_exit("...");  // Leaks map data and potentially MLX resources!
```

**Mitigation**: OS reclaims memory on exit
**Best Practice**: Call `free_resources()` before each `exit()`

### 5. **File Parsed Three Times**

**Operations**:
1. `get_map_dimensions()` - Full file scan
2. `allocate_map()` - Allocates memory
3. `parse_map_data()` - Full file scan again

**Why**: Need dimensions before allocation
**Alternative**: Single-pass with dynamic reallocation (more complex)
**Impact**: Slower startup for large files, but cleaner code

### 6. **No Error Recovery**

**Current Behavior**: Any error is fatal (exit 1)

**No handling for**:
- Malformed input (mismatched row lengths)
- Non-integer tokens
- Empty files
- Memory exhaustion

**User Experience**: Abrupt termination with generic message

### 7. **Hard-Coded Constants**

**Scattered Magic Numbers**:
- Rotation sensitivity: `0.01`
- Zoom step: `2`
- Minimum zoom: `2`
- Isometric angle: `0.523599`
- Color scheme count: implicit (0-4)

**Best Practice**: Define as named constants or enums
**Impact**: Harder to tune and maintain

### 8. **Platform Dependencies**

**Linux-Specific**:
- `mlx_do_sync()` - Not available on macOS
- Key codes (65307, etc.) - X11 specific
- Mouse button numbers - X11 specific

**Portability**: Would need conditional compilation for macOS

### 9. **No Anti-Aliasing**

**Current**: Jagged lines (aliasing artifacts)
**Why**: Bresenham produces hard pixels
**Alternative**: Wu's algorithm (anti-aliased lines)
**Trade-off**: Performance vs. quality

### 10. **Frame Rate Not Controlled**

**Issue**: Redraws as fast as possible
**Impact**:
- Wasted CPU/GPU on idle frames
- No consistent motion speed
- Battery drain on laptops

**Solution**: Cap frame rate or redraw only on changes (already doing latter)

---

## Performance Characteristics

### Time Complexity

**Startup**:
- File reading: O(width × height)
- Memory allocation: O(height) + O(width × height)
- Statistics calculation: O(width × height)
- **Total**: O(width × height)

**Rendering**:
- Map drawing: O(width × height × average_line_length)
- Line drawing: O(|x2-x1| + |y2-y1|) per line
- **Per frame**: O(width × height) wireframe edges

**Event Handling**: O(1) for all events

### Space Complexity

**Memory Usage**:
- z_matrix: `width × height × sizeof(int)` = 4 bytes per point
- color_matrix: `width × height × sizeof(int)` = 4 bytes per point (wasted!)
- Image buffer: `1200 × 800 × 4` = 3.84 MB (constant)
- **Total**: ~8 × width × height bytes + 3.84 MB

**Example** (100×100 map):
- z_matrix: 40 KB
- color_matrix: 40 KB (unused)
- Image buffer: 3.84 MB
- **Total**: ~3.92 MB

### Bottlenecks

1. **Redraw frequency**: Every user interaction triggers full redraw
2. **Large maps**: O(n²) lines to draw for n×n grid
3. **No culling**: Draws off-screen lines
4. **No LOD**: Zoomed out still draws every line

**Optimizations Possible**:
- Spatial culling (don't draw off-screen)
- Level of detail (fewer lines when zoomed out)
- Dirty rectangles (only redraw changed regions)
- GPU acceleration (OpenGL instead of software rendering)

---

## Testing Observations

### Test Maps Available

**Simple Tests**:
- `single.fdf` - Single point
- `tiny.fdf` - Minimal 2×2 grid
- `flat.fdf` - No elevation (z=0 everywhere)
- `simple.fdf` - Basic test case

**Complex Tests**:
- `42.fdf` - 42 school logo
- `mars.fdf` - Mars elevation data
- `julia.fdf` - Julia set fractal
- `pyramide.fdf` - Pyramid shape

**Edge Cases**:
- `empty.fdf` - Should fail gracefully
- `elem-fract.fdf` - Fractional numbers
- `elem-col.fdf` - Color specifications
- `pentenegpos.fdf` - Negative elevations

### Expected Behaviors

**Good Maps**: Smooth rendering, no crashes
**Malformed Maps**: Undefined (may crash)
**Empty Files**: Should fail with error message
**Missing Files**: Caught by `is_valid_file()`

---

## Future Enhancement Ideas

### Functional Enhancements

1. **Color Parsing**: Implement hex color extraction from FDF files
2. **Multiple Projections**: Parallel, perspective, orthographic
3. **Z-axis Rotation**: Implement gamma rotation (roll)
4. **Animation**: Automatic rotation toggle
5. **Screenshot**: Save current view to image file

### Technical Improvements

1. **Fix main() Logic**: Check argc before using argv
2. **Remove color_matrix**: Eliminate wasted memory
3. **Add Error Recovery**: Graceful handling of malformed input
4. **Proper Cleanup**: Free resources before all exits
5. **Single-Pass Parsing**: Reduce file I/O

### Performance Optimizations

1. **Frustum Culling**: Don't draw off-screen lines
2. **Delta Rendering**: Only redraw on actual changes
3. **GPU Rendering**: Port to OpenGL/Vulkan
4. **Multi-threading**: Parallel line drawing
5. **Spatial Indexing**: Octree for large maps

### Code Quality

1. **Named Constants**: Replace magic numbers
2. **Error Enums**: Structured error types
3. **Unit Tests**: Automated test suite
4. **Documentation**: Inline comments for complex logic
5. **Valgrind Clean**: Fix all memory leaks

---

## Architecture Strengths

### What's Done Well

1. **Modular Design**: Clear separation of concerns
2. **Single Responsibility**: Each file has focused purpose
3. **Clean Data Flow**: Unidirectional data dependencies
4. **Defensive Programming**: Null checks and bounds checking
5. **Readable Code**: Consistent naming and formatting

### Design Patterns Used

1. **Data-Oriented Design**: Structures group related data
2. **Event-Driven Architecture**: Callbacks for user input
3. **Double Buffering**: Off-screen rendering prevents flicker
4. **Factory Pattern**: `init_*()` functions for setup
5. **Resource Acquisition Is Initialization (RAII)**: Stack cleanup

---

## Conclusion

This FDF implementation is a solid, functional wireframe renderer with interactive controls. It successfully demonstrates:

- 3D graphics fundamentals
- File parsing and data structures
- Event-driven programming
- Memory management in C
- Mathematical transformations

**Strengths**:
- Clean, modular architecture
- Smooth interactive controls
- Multiple color schemes
- Handles various map sizes
- Stable and crash-resistant (mostly)

**Weaknesses**:
- Color parsing not implemented
- Some memory leaks on error paths
- Unused structure members
- Argument validation timing bug
- Platform-specific code

**Overall**: Production-ready for its intended scope (42 school project), with room for enhancements if extended into a full-featured tool.

---

*Analysis Generated: 2025-11-11*
*Codebase Version: ft_linux branch*
*Total Lines of Code: ~1,500 (excluding libraries)*

