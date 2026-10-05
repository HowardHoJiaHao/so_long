# so_long

> 42 Common Core · Rank 02

A small top-down 2D game built with the **MiniLibX** graphics library. The player collects every item on the map and then reaches the exit.

## Features
- Map loading from a `.ber` file with full validation (rectangular, closed by walls, exactly one player and exit, at least one collectible)
- **Flood fill** check to make sure every collectible and the exit are reachable
- Sprite rendering, keyboard controls (W/A/S/D) and move counter
- Clean exit on window close or `ESC`, no memory leaks

## Usage (Linux)
```bash
make
./so_long map/<map_name>.ber
```
