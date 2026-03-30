# MyGKrellm

> Made by **Marlon PEGAHI**, **Edgar MAUREL**, **Allan LEHERPEUX** and **Alexandre BRET**

A modular system monitoring application inspired by [GKrellm](http://gkrellm.srcbox.net/), built in C++20. It displays real-time system metrics through a pluggable module system and supports multiple display backends dynamically, a terminal (ncurses) view and a graphical (SFML) window.

---

## Features

- Real-time monitoring of CPU, RAM, battery, network, processes, and system info
- Two interchangeable display backends: terminal (ncurses) and GUI (SFML)
- Clean plugin architecture — easy to extend with new modules or display backends
- Built with modern C++20

---

## Dependencies

| Library | Purpose |
|---------|---------|
| [SFML](https://www.sfml-dev.org/) | Graphical display backend (graphics, window, system) |
| [ncurses](https://invisible-island.net/ncurses/) | Terminal display backend |

Install on Arch Linux:
```sh
sudo pacman -S sfml ncurses
```

Install on Debian/Ubuntu:
```sh
sudo apt install libsfml-dev libncurses-dev
```

---

## Build

```sh
make        # Build
make re     # Full rebuild
make clean  # Remove object files
make fclean # Remove object files and binary
```

---

## Usage

```sh
./MyGKrellm [DISPLAY_TYPE]
```

| Value | Backend |
|-------|---------|
| `0`   | Ncurses (terminal) |
| `1`   | SFML (graphical window) |

**Examples:**
```sh
./MyGKrellm 0   # Launch in terminal mode
./MyGKrellm 1   # Launch in GUI mode
```

---

## Architecture

MyGKrellm is built around two interfaces:

- **`IModule`** — provides system data. Each module implements `update()` and returns a tuple of `(name, value, display_type)`.
- **`IDisplay`** — renders data. Each backend implements `open()`, `close()`, `clear()`, `event()`, and `display()`.

The `KrellCore` engine manages the lifecycle: it registers modules and displays, selects the active backend, then runs the main loop (clear → events → update → render).

### Modules

| Module | Description |
|--------|-------------|
| `CpuInfo` | Per-core CPU usage (reads `/proc/stat`) |
| `Ram` | Memory usage |
| `Battery` | Battery status |
| `NetworkLoad` | Network bandwidth |
| `ProcessusInfo` | Running process information |
| `SystemInfo` | Hostname, uptime |
| `DateTime` | Current date and time |

### Display Backends

| Backend | Description |
|---------|-------------|
| `NcurseDisplay` | Terminal rendering with bars and text |
| `SFMLDisplay` | 800×600 GUI window, loads font from `assets/fonts/font.otf` |

---

## Extending the Project

### Add a new module

1. Create `src/modules/MyModule.cpp` and `src/include/MyModule.hpp` implementing `IModule`
2. Add the `.cpp` to `SRC` in `Makefile`
3. Register it in `Main.cpp` with `krell.addModule(myModule)`

### Add a new display backend

1. Create your display class implementing `IDisplay` in `src/displays/`
2. Add a new entry to the `DisplayType` enum in `src/interface/IDisplay.hpp`
3. Register it in `Main.cpp` and handle the new CLI argument value

---

## Project Structure

```
MyGKrellm/
├── assets/fonts/         # Font used by SFML display
├── src/
│   ├── Main.cpp          # Entry point
│   ├── Krell.cpp         # Core engine
│   ├── interface/        # IModule and IDisplay abstract interfaces
│   ├── include/          # Headers for all modules and displays
│   ├── modules/          # System info module implementations
│   └── displays/         # Ncurses and SFML display implementations
└── Makefile
```
