# 🚖 TaxiGame

[![C++](https://img.shields.io/badge/C++-26-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-2.5.1-green.svg)](https://www.sfml-dev.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)]()
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)]()

**TaxiGame** is a C++ desktop application built with **SFML** that simulates an interactive **taxi fleet catalog and management system**. Browse through **200+ realistic car models** organized by **service tiers**, manage your fleet with a virtual economy, and switch between major ride-hailing modes like **YandexGo** and **Uber**.

---

## ✨ Features

### 🚗 Extensive Car Database
- **200+ vehicles** from global manufacturers: Audi, BMW, Toyota, Mercedes, Chery, Geely, Hyundai, Kia, Volkswagen, Rolls Royce, Bentley, and more.
- Each car includes:
  - **Model name** with individual car image (`source/Car Images/`)
  - **Service tier** (Economy, Comfort, Comfort+, Business, Cruise, Premier, Elite, Minivan)
  - **Passenger capacity**
  - **Base fare** per kilometer
  - **Purchase price**
  - **Ownership status**

### 🏷️ Tiered Service Categories

| Tier | Base Fare | Capacity | Example Vehicles |
|------|-----------|----------|------------------|
| **Economy** | $1.49/km | 4 | Hyundai Solaris, Kia Rio, Lada Vesta |
| **Comfort** | $1.69/km | 4 | Audi A6, Kia K5, Toyota Camry |
| **Comfort+** | $3.50/km | 4 | BMW 5 Series, Genesis G80 |
| **Business** | $10/km | 3 | Audi A8, Mercedes S-Class |
| **Cruise** | $12/km | 6 | Mercedes V-Class |
| **Premier** | $15/km | 3–6 | Rolls Royce Ghost |
| **Elite** | $20/km | 3–6 | Bentley Flying Spur |
| **Minivan** | $7/km | 6 | Kia Carnival |

### 🎮 Interactive Gameplay
- **Fleet Management**: Start with **$65,000** and buy cars to build your taxi fleet.
- **Ownership Tracking**: Purchased cars are marked as **OWNED** in green; unowned cars show their price in red.
- **Fare Calculator**: `fare = baseFare + (distance × 1.76)` for each vehicle.
- **Car Browsing**: Navigate through cars one-by-one with **Left / Right Arrow** keys.

### 🖱️ Rich User Interface
- **Main Menu Buttons**: `Exit`, `CarsList`, `MainMenu`, `ModeSelect`
- **Tier Filter Buttons**: Filter cars by service tier (Economy, Comfort, etc.)
- **Mode Selection**: Switch between taxi platforms (e.g., **YandexGo**, **Uber**)
- **Hover Effects**: Buttons glow **red** on mouse hover
- **Click Sounds**: Audio feedback on every button press (`sound/click.wav`)
- **Custom Visuals**: Full-screen background (`images/background.jpg`) + OpenSans typography

### 🎵 Audio & Polish
- Startup and exit sound effects
- 120 FPS frame limit for smooth rendering
- Clean 1000×1000 pixel window

---

## 🎮 Controls

| Input | Action |
|-------|--------|
| **Mouse** | Hover over buttons, click to interact |
| **← / →** | Browse previous / next car in current tier |
| **M** | Return to **Main Menu** |
| **C** | Go to **Car List** (Economy tier) |
| **Escape** | Exit application |
| **Numpad 3** | Cheat: **+$10,000** money |
| **Numpad 9** | Cheat: **+$100,000** money |
| **Numpad 1** | Cheat: **−$100,000** money |

---

## 🛠️ Build & Run (Windows)

All dependencies are **bundled** in the repository — no external installation required.

### Prerequisites
- Windows OS
- MinGW (included in `required/MinGW/`)
- SFML 2.5.1 (included in `required/SFML-2.5.1/`)

### Build
```bash
make
```
This compiles `main.cpp` → `main.o` → `TaxiGame.exe` using static linking for all SFML modules.

### Run
```bash
TaxiGame.exe
```
Or simply double-click `TaxiGame.exe` in File Explorer.

> ⚠️ Ensure the following files/folders are in the same directory as the executable:
> - `images/background.jpg`
> - `sound/click.wav`, `sound/start.wav`, `sound/stop.wav`
> - `OpenSans-Italic-VariableFont_wdth,wght.ttf`
> - `source/Car Images/` (individual car PNGs)

---

## 📁 Project Structure

```
TaxiGame/
├── main.cpp                          # Entry point & game loop
├── makefile                          # MinGW build script (static SFML)
├── README.md                         # This file
├── Documentation.md                  # Detailed architecture docs
│
├── source/
│   ├── Class/
│   │   ├── TaxiGameClass.h           # Main game state & UI manager
│   │   ├── CarClass.h                # Vehicle data model
│   │   └── ButtonClass.h             # Interactive UI button component
│   ├── functions/
│   │   ├── mouseMove.h               # Mouse hover detection
│   │   ├── mouseClick.h              # Mouse click handling
│   │   ├── viewAllCarsFunc.h         # Car catalog renderer
│   │   ├── MainMenuButtonsView.h     # Main menu rendering
│   │   ├── TierButtonsView.h         # Tier filter rendering
│   │   ├── ModeButtonsView.h         # Mode selection rendering
│   │   ├── adjustScroll.h            # Scroll bounds logic
│   │   ├── ButtonAdd.h               # Button creation helper
│   │   └── soundLoad.h               # Audio asset loading
│   ├── Lists/
│   │   ├── MainMenuButtonsList.h     # Main menu button definitions
│   │   ├── ModeButtonsList.h         # Mode button definitions
│   │   ├── YandexGo/                 # YandexGo car databases
│   │   │   ├── YandexGo_Economy.h
│   │   │   ├── YandexGo_Comfort.h
│   │   │   ├── YandexGo_ComfortPlus.h
│   │   │   ├── YandexGo_Business.h
│   │   │   ├── YandexGo_Cruise.h
│   │   │   ├── YandexGo_Premier.h
│   │   │   ├── YandexGo_Elite.h
│   │   │   ├── YandexGo_Minivan.h
│   │   │   └── YandexGo-TierButtonsList.h
│   │   └── Uber/                     # (Future Uber car databases)
│   ├── carslist.h                    # Aggregates all car data files
│   ├── GameStart.h                   # Window, font & game initialization
│   ├── TierButtonsInit.h             # Tier button setup
│   ├── ModeButtonsInit.h             # Mode button setup
│   ├── MainMenuButtonsInit.h         # Main menu button setup
│   ├── buybutton.h                   # Purchase button logic
│   ├── viewAllCarsFunc.h             # Car display renderer
│   └── soundLoad.h                   # Sound buffer loading
│
├── images/
│   └── background.jpg                # Game background
│
├── sound/
│   ├── click.wav                     # Button click SFX
│   ├── start.wav                     # Startup SFX
│   └── stop.wav                      # Exit SFX
│
├── source/Car Images/                # Individual car PNGs (e.g., "Kia Rio.png")
│
├── required/
│   ├── MinGW/                        # GCC 8.1.0 compiler toolchain
│   ├── SFML-2.5.1/                   # Static SFML libraries & headers
│   └── make-3.81.exe                 # Windows Make utility
│
└── openal32.dll                      # OpenAL audio driver
```

---

## 🏗️ Architecture Overview

### Core Classes

#### `TaxiGame` (`source/Class/TaxiGameClass.h`)
The central game controller managing:
- `vector<Car> cars` — full vehicle database
- `vector<Button> mainButtons / tierButtons / modeButtons` — UI layers
- `long long money` — player currency (starts at $65,000)
- `string currentTier / currentMode` — active filters
- `scrollY` — vertical scroll position

Key methods:
- `initializeCars()` — loads 200+ cars from header data files
- `viewAllCars()` — renders current car image, stats, and ownership status
- `handleMouseMoved()` / `handleMouseClicked()` — input processing
- `initializeMainButtons()` / `initializeTierButtons()` / `initializeModeButtons()` — UI setup

#### `Car` (`source/Class/CarClass.h`)
Data model for each vehicle:
```cpp
Car(model, capacity, baseFare, tier, buyPrice, owned, quantity)
```
- `calculateFare(distance)` → `baseFare + (distance × 1.76)`

#### `Button` (`source/Class/ButtonClass.h`)
SFML-powered UI element with:
- `sf::RectangleShape` + `sf::Text`
- `isClicked(x, y)` — hit detection
- `setHovered(bool)` — color change to red

### Rendering Pipeline
1. Clear window (black)
2. Draw background sprite
3. **If MainMenu**: render main menu buttons only
4. **If ModeSelect**: render main menu + mode selection buttons
5. **If Car List**: render current car image + info, main menu buttons, tier filter buttons
6. Display frame

---

## 🖼️ Screenshots

> *Add your screenshots here:*
>
> ```
> [Main Menu]
> [Car Browser - Economy Tier]
> [Mode Selection Screen]
> ```

---

## 🗺️ Roadmap & Future Plans

- [ ] Implement full **CarSend** dispatch feature
- [ ] Add **distance input UI** for real-time fare calculation
- [ ] Expand **Uber** mode with dedicated car lists
- [ ] Add more car images for all 200+ models
- [ ] Polish UI/UX with animations and transitions
- [ ] Save/load fleet progress to file

---

## 📄 License

- **Project Code**: MIT License
- **SFML**: See [`required/SFML-2.5.1/license.md`](required/SFML-2.5.1/license.md)
- **OpenSans Font**: SIL Open Font License

---

## 🤝 Contributing

1. Fork the repository
2. Build with `make` to verify compilation
3. Add cars, tiers, or features in `source/`
4. Submit a Pull Request

**Built with ❤️ using C++ & SFML. Start your taxi empire today! 🚕**

