# TetrisMinesSweeper

> A hybrid between Tetris and Minesweeper.

[Español](README.es.md) | **English** | [Português](README.pt.md)

![Status](https://img.shields.io/badge/status-WIP%20%2F%20prototype-orange)
![Language](https://img.shields.io/badge/language-C-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green)

TetrisMinesSweeper is a PC game that fuses two classics:

- **Tetris**: the same pieces as always fall from above. You move them, rotate them, and try to place them well.
- **Minesweeper**: each piece carries one or more hidden mines. When it lands, its cells become part of the board as minesweeper tiles, showing the number of adjacent mines around them.

The key mechanic is that **a line is not cleared just by filling it**. You must first unlock all the white cells in that row — the ones that don't contain a mine. Detonating a mine or mismanaging the board will penalize you. The score combines the speed and efficiency of Tetris with the precision of Minesweeper.

---

## Project Status

**Prototype under development.** Currently implemented:

- [x] 10×20 board centered on screen
- [x] All 7 standard Tetris pieces with their colors
- [x] Piece movement and rotation
- [x] Cell structure with mine fields and adjacent mine count
- [x] Basic screens: Logo → Title → Gameplay → Ending
- [x] Collision detection with the floor and other pieces
- [x] Automatic gravity drop

Still missing (work in progress):

- [ ] Mine assignment when generating each piece
- [ ] Adjacent number update on landing
- [ ] Cell unlock logic and line clearing
- [ ] Scoring system
- [ ] Next piece / hold piece display
- [ ] Levels and progression
- [ ] Menus
- [ ] UI
- [ ] Artwork (assets)

---

## Building

### Requirements

- [raylib](https://www.raylib.com/) (tested with raylib 4.x or higher)
- C99-compatible compiler or later (`gcc` on Linux, MinGW on Windows)
- [Code::Blocks](https://www.codeblocks.org/) with a compiler configured

### Windows (Code::Blocks)

1. Clone or download the repository.
2. Open the `.cbp` file with Code::Blocks.
3. Make sure the raylib path is correctly set in the project options:
   - **Build Options → Search directories**: path to `raylib/include`
   - **Build Options → Linker settings**: `raylib`, `opengl32`, `gdi32`, `winmm`
4. Build and run with `F9`.

### Linux (command line)

```bash
gcc main.c escenario.c pieza.c -o tetris_mines \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./tetris_mines
```

> On some distributions you may need to install raylib from your package manager or build it from source: https://github.com/raysan5/raylib

---

## Project Structure

```
TetrisMinesSweeper/
├── main.c          # Main loop and screen management
├── escenario.h     # Board, cell definitions and constants
├── escenario.c     # Board initialization and rendering
├── pieza.h         # Piece and block definitions
├── pieza.c         # Piece logic: init, movement, rotation
└── README.md
```

---

## Key Constants

| Constant | Value | Description |
|---|---|---|
| `COLUMNAS` | 10 | Board width in cells |
| `FILAS` | 20 | Board height in cells |
| `CELDA_SIZE` | 40px | Pixel size of each cell |
| `PIEZA_BLOQUES` | 4 | Blocks per piece |
| `PIEZA_TIPOS` | 7 | Number of piece types (I O T S Z J L) |

---

## License

This project is licensed under the **MIT License**. You are free to use, modify and distribute it as long as you keep the original copyright notice.

```
MIT License — Copyright (c) 2026 Tuken
```

---

## Credits

- Built with [raylib](https://www.raylib.com/) by Ramon Santamaria [@raysan5](https://x.com/raysan5)
- Inspired by Tetris and Minesweeper
- The original concept was inspired by [Itch.io](https://kertisjones.itch.io/tetrisweeper) user Kertis Jones [@KertisJones](https://x.com/KertisJones), who made this fusion before me
