# Chess Engine

A chess engine written from scratch in C, featuring a complete rules implementation, an
adversarial-search AI, and an interactive GUI built with [raylib](https://www.raylib.com/).

Created by **Mack Greenlaw** and **Evelyn**.

## Features

- **Full chess rules** — legal move generation for all six piece types, plus check,
  checkmate, stalemate, and en passant detection.
- **AI opponent** — move search using the **minimax** algorithm with **alpha–beta pruning**
  to a configurable depth.
- **Move ordering** — **MVV–LVA** (Most Valuable Victim, Least Valuable Aggressor) heuristic
  to improve pruning efficiency and search speed.
- **Position evaluation** — a heuristic combining material balance with **piece-square
  tables** to reward strong positional play and piece mobility.
- **Graphical interface** — a 60 FPS GUI (main menu + in-game board) rendered with raylib.
- **Cross-platform build** — an OS-agnostic Makefile targeting Windows and macOS.

## Tech stack

| Area            | Details                                  |
| --------------- | ---------------------------------------- |
| Language        | C (C11)                                  |
| Graphics / GUI  | raylib (bundled in `lib/raylib`)         |
| Build           | GNU Make, gcc, `-O2`                      |
| Platforms       | Windows, macOS                           |

## Getting started

### Prerequisites

- `gcc` and `make`
- raylib's system dependencies (OpenGL). raylib itself is vendored in `lib/raylib`.
  - **Windows:** MinGW-w64 (provides `gcc` and the required libs).
  - **macOS:** install raylib via Homebrew — `brew install raylib`.

### Build & run

```bash
# Build the executable
make

# Build and launch
make run

# Remove build artifacts
make clean
```

This produces the `chess-engine` executable (`chess-engine.exe` on Windows).

## How to play

1. Launch the program and select **Play** from the main menu.
2. Click a piece to select it; legal destination squares are highlighted.
3. Click a highlighted square to move. The engine responds with its computed move.
4. Play continues until checkmate or stalemate. Use the in-game controls to reset or return
   to the menu.

## Project structure

```
src/
├── main.c               # Entry point and main program loop
├── board.c / board.h    # Board state, move generation, check/mate/stalemate logic
├── gui.c / gui.h        # raylib rendering, menus, and input handling
├── piece.h              # Piece type/color encoding
├── program_state.h      # Top-level program states (menu / in-game)
└── strategy/
    ├── move_tree.c/.h   # Minimax + alpha–beta search and move selection
    ├── payoff.c/.h      # Evaluation: material + mobility scoring
    └── pst.h            # Piece-square tables
lib/raylib/              # Vendored raylib graphics library
res/                     # Piece textures and assets
Makefile                 # Cross-platform build
```

## How the engine works

The AI selects moves with a depth-limited **minimax** search, treating White as the
maximizing player and Black as the minimizing player. **Alpha–beta pruning** discards
branches that cannot affect the outcome, and **MVV–LVA** move ordering searches likely-strong
captures first to trigger more cutoffs.

At the search horizon, each position is scored by an evaluation function that sums:

- **Material** — the weighted difference in remaining pieces between the two sides.
- **Mobility / position** — per-piece **piece-square table** bonuses that encourage pieces
  toward strong squares.

Terminal positions return a large magnitude score for checkmate and zero for stalemate.

## Authors

- Mack Greenlaw — [@mgreenlaw10](https://github.com/mgreenlaw10)
- Evelyn

## Acknowledgements

- [raylib](https://www.raylib.com/) — simple and easy-to-use library for graphics and input.
