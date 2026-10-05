# so_long

> 42 Common Core · Rank 02

The purpose of this project is to make a small top-down 2D game with **MiniLibX**, 42's simple graphics library for the X Window System. It covers opening a window, handling keyboard and window events, drawing sprites, and reading and validating a map file.

The player has to collect every key on the map and then reach the exit, using as few moves as possible.

## Controls
| Key | Action |
|:--:|---|
| `W` / `A` / `S` / `D` | Move up / left / down / right |
| `ESC` or the window's close button | Quit the game |

The number of moves is shown at the top left of the window and printed in the terminal after each move. Walls block movement. Walking onto a key collects it. The exit only ends the game once every key has been collected, and then the terminal prints `Victory! N MOVES made`.

## Map format
A map is a text file with the `.ber` extension, made of these characters:

| Character | Meaning |
|:--:|---|
| `1` | Wall |
| `0` | Floor |
| `C` | Collectible (a key) |
| `E` | Exit |
| `P` | Player's starting position |

Example (`map/map1.ber`):
```
1111111111111
10E00000000C1
1110011110001
1P00110000001
1111111111111
```

A map is only accepted if:
- it is rectangular,
- it is completely surrounded by walls,
- it uses only the characters above,
- it has exactly one `P`, exactly one `E` and at least one `C`,
- every `C` and the `E` can be reached from the player's start.

## How it works
1. **Arguments** – Checks there is exactly one argument, that the file opens, and that it ends in `.ber`.
2. **Reading the map** – Reads the file line by line with `get_next_line`, checking that every line has the same width, and builds a 2D grid.
3. **Validation** – Checks the characters, the number of `P`, `E` and `C`, and that the border is all walls.
4. **Flood fill** – Starting from the player, a copy of the grid is "painted" tile by tile through everything that is not a wall. If any `C` or `E` is left unpainted, it cannot be reached and the map is rejected. The exit is not walked through, so a key that can only be reached by crossing the exit counts as unreachable.
5. **Window and sprites** – Opens a window of 64 × 64 pixels per tile and loads 8 XPM sprites: wall, floor, key, exit, and the player facing front, back, left and right.
6. **Drawing** – Every frame, the whole map is drawn into an off-screen image first, skipping transparent pixels so sprites sit on top of the floor. That image is then put on the window in one go, which avoids flickering.
7. **Quitting** – On `ESC`, the close button or a win, all images, the window, the display connection and the map memory are freed.

## Error handling
For an invalid map or argument, the game prints `Error` followed by a message and exits with status `1`:

| Message | Cause |
|---|---|
| `Wrong number of arguments` | Not exactly one map file given |
| `Unable to open map file` | The file does not exist or cannot be read |
| `Bad file extension` | The file does not end in `.ber` |
| `Map is Not Rectangle` | Lines have different lengths |
| `Map has Unknown Character` | A character other than `0 1 C E P` |
| `Asset Insufficient` | Not exactly one `P` and one `E`, or no `C` |
| `Map not surrounded by walls` | A border tile is not `1` |
| `Some exit or collectibles cannot be reached` | The flood fill could not reach a `C` or the `E` |
| `failed to init mlx ptr` | No display available (e.g. no X server) |
| `Sprite was not found` | An image in `assets/` is missing |

## Project structure
| Path | Contents |
|---|---|
| `srcs/main.c` | Argument checks and the MiniLibX event hooks |
| `srcs/check_map.c` | Reading the map and validating it |
| `srcs/flood_fill.c` | Flood fill reachability check |
| `srcs/error_handling.c` | Error messages and freeing memory |
| `srcs/mlx.c` | Window, sprite loading and closing the game |
| `srcs/keyboard.c`, `srcs/moves.c` | Key handling, movement, collecting and winning |
| `srcs/render.c`, `srcs/render2.c` | Drawing the map and player into the frame |
| `includes/so_long.h` | Structures and prototypes |
| `libft/` | My [libft](https://github.com/HowardHoJiaHao/libft), with `ft_printf` and `get_next_line` |
| `mlx/` | MiniLibX (BSD 2-Clause License, © École 42) |
| `assets/` | XPM sprites |
| `map/` | Example maps |

## Clone
Clone the repository:
```bash
git clone https://github.com/HowardHoJiaHao/so_long.git
```

## Compile and Run
The game runs on Linux and needs the X11 libraries that MiniLibX uses:
```bash
sudo apt install libx11-dev libxext-dev zlib1g-dev
```

To compile, `cd` into the cloned directory and run:
```bash
make
```

This builds `libft`, MiniLibX and then the `so_long` executable. Other targets: `make clean` (remove object files), `make fclean` (also remove the executables) and `make re` (rebuild from scratch).

To run the program, pass a map file. Run it from the repository folder, because the sprites are loaded from `assets/`:
```bash
./so_long map/map1.ber
```

More maps:
- `map/maps_valid/` – 16 more playable maps.
- `map/maps_err/` – 53 invalid maps (bad extension, missing walls, unreachable keys, …). Each one is rejected with the matching error:
  ```bash
  for f in map/maps_err/*; do echo "$f"; ./so_long "$f"; done
  ```
