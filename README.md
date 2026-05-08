# TaxiGame

[![C++](https://img.shields.io/badge/C++-26-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-2.5.1-green.svg)](https://www.sfml-dev.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A taxi management simulation game built with C++ and SFML. Manage your taxi fleet by buying cars, selecting colors, and operating in different modes like YandexGo and Uber.

## Features

- **Car Management**: Browse and purchase cars across different tiers (Economy, Comfort, Business, etc.)
- **Color Selection**: Choose car colors (Black, White, Red, Blue) for customization
- **Multiple Modes**: Switch between YandexGo and Uber service modes
- **Fleet Operations**: Send cars on rides and earn money
- **Tier Filtering**: Filter cars by service tier
- **Interactive UI**: Click buttons to navigate menus and make purchases

## Requirements

- C++ compiler (g++ recommended)
- SFML 2.5.1 (static linking)
- Windows (PowerShell for build scripts)

## Building

1. Ensure SFML is installed in `./required/SFML-2.5.1/`
2. Run the build command:
   ```bash
   g++ -c main.cpp -D SFML_STATIC -DAL_LIBTYPE_STATIC -I"./required/SFML-2.5.1/include" -o main.o
   g++ main.o -o TaxiGame.exe -L"./required/SFML-2.5.1/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lwinmm -lgdi32
   ```

## Running

Execute `TaxiGame.exe` to start the game.

## Controls

- **Mouse**: Click buttons and interact with UI
- **M**: Open Main Menu
- **C**: Switch to Car List
- **Num3**: Add $10,000 (cheat)
- **Num9**: Add $100,000 (cheat)
- **Num1**: Subtract $100,000 (cheat)
- **Escape**: Exit game
- **Arrow Keys**: Navigate cars in list view

## Game Modes

- **YandexGo**: Russian ride-hailing service
- **Uber**: International ride-hailing service

Each mode has different car tiers and pricing.

## File Structure

- `main.cpp`: Main game loop
- `source/`: Source code directory
  - `Class/`: Game classes (Car, Button, TaxiGame)
  - `functions/`: UI and interaction functions
  - `Lists/`: Car data lists organized by mode and tier
- `images/`: Game assets (background, car images)
- `sounds/`: Audio files

## Development

The game uses SFML for graphics, audio, and window management. Car data is stored in header files for easy modification. Add new cars by editing the appropriate list files in `source/Lists/`.

## License

This project is for educational purposes.</content>
<parameter name="filePath">H:\TaxiGame\README.md