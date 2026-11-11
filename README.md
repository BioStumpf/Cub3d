*This project has been created as part of the 42 curriculum by nildruon, dstumpf.*

# cub3D

## Description

**cub3D** is a 3D graphical project inspired by the world-famous 1992 classic *Wolfenstein 3D* by id Software, widely considered the first true first-person shooter (FPS).

The goal of this project is to build a dynamic first-person view inside a maze using the principles of **raycasting** and the **MiniLibX** graphical library in C. Unlike modern 3D engines that rely on polygonal meshes and GPU shaders, a raycaster projects a 3D perspective from a 2D grid map by casting one ray per vertical column of the screen and computing wall distances using the **Digital Differential Analyzer (DDA)** algorithm.

### Key Features
- **Scene & Map Parsing**: Reads `.cub` scene description files specifying North, South, East, and West wall textures (`.xpm`), Floor and Ceiling RGB colors, and a closed 2D maze grid.
- **Map Validation**: Ensures all configuration elements are valid, textures can be loaded, RGB values are within `[0, 255]`, a single player spawn exists (`N`, `S`, `E`, or `W`), and the map is completely enclosed by walls (`1`).
- **DDA Raycasting Engine**: Casts rays across the player's field of view at a resolution of `1920x1080`, calculating perpendicular wall distances to prevent fish-eye distortion.
- **Textured Walls**: Maps directional XPM textures onto vertical wall slices depending on the cardinal orientation of the wall face hit (`NORTH`, `SOUTH`, `EAST`, `WEST`).
- **Smooth Controls & Collision Detection**: Frame-rate independent movement and camera rotation using delta time (`gettimeofday`), complete with wall collision buffers.

---

## Instructions

### Prerequisites
- A Linux environment with the **X11** windowing system.
- `cc` (Clang) and `make`.
- **MiniLibX** (`-lmlx`) and X11 development libraries (`-lXext`, `-lX11`, `-lm`).

### Compilation
Clone the repository and run `make` at the root of the project:

```bash
make
```

Available `Makefile` rules:
- `make` or `make all` — Compiles `libft` and builds the `cub3D` executable.
- `make clean` — Removes object (`.o`) and dependency (`.d`) files.
- `make fclean` — Removes object/dependency files and the `cub3D` binary.
- `make re` — Performs a full recompilation (`fclean` followed by `all`).
- `make norm` — Runs the norminette check script (`./norm.sh`).

### Execution
Run the executable by passing a valid `.cub` map file as its sole argument:

```bash
./cub3D lol.cub
```

### Controls
| Key | Action |
| :--- | :--- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (Left Arrow) | Rotate camera left |
| `→` (Right Arrow) | Rotate camera right |
| `ESC` / Window `X` | Exit the program cleanly |

### Map Format (`.cub`)
A valid `.cub` file consists of two parts: the **scene configuration data** followed by the **2D map grid**, which **must always be last** in the file.

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,3
C 225,30,0

111111
1000N1
101001
111111
```

#### Scene Configuration Data Rules
- **Elements**:
  - `NO`, `SO`, `WE`, `EA`: Paths to the XPM textures for each wall orientation.
  - `F`, `C`: Floor and Ceiling colors in `R,G,B` format (`0–255`).
- **Ordering**: The configuration elements above the map can appear in **any order**, as long as all of them are defined **before** the map starts (no configuration data is allowed after the map).
- **Whitespace**: Leading, trailing, and one or multiple spaces between an identifier and its value are allowed (e.g., `"  EA   ./textures/west.xpm  "`).
- **Line Separators**: Empty lines separating configuration elements must consist strictly of a newline (`\n`).

#### Map Grid Rules
- **Position**: The map **must be the very last element** in the `.cub` file.
- **Allowed Characters**:
  - `' '` (literal space character only — **no tabs** or other whitespace characters)
  - `'1'` (wall)
  - `'0'` (walkable floor)
  - `'N'`, `'S'`, `'E'`, or `'W'` (single player starting position and cardinal spawn orientation)
- **Line Endings**: Each line of the map is separated by a `\n`, **except the very last line** (no trailing newline after the final map row).
- **Enclosure**: The map must be completely surrounded by walls (`1`) — no walkable floor (`0`) or player cardinal direction (`N`, `S`, `E`, `W`) is allowed on the outer border of the map or adjacent to spaces.

---

## Resources

### Classic References
- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html): The definitive guide to DDA raycasting, camera plane mathematics, perpendicular wall distance, and texture mapping.

### AI Usage
AI tools were used during the development of this project for the following tasks:
- **Mathematical & Conceptual Clarification**: Reviewing vector rotation formulas, camera plane projection math, and the DDA step-size calculations to avoid fish-eye distortion.
- **Documentation**: Structuring and drafting this `README.md` file in accordance with the 42 subject specifications.
