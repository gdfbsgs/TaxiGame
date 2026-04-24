# TaxiGame - C++ SFML Application Documentation

## Overview
TaxiGame is a desktop application built with C++ and SFML that simulates a taxi car catalog and management system. Users can browse 200+ car models organized by service tiers, calculate fares, and interact via keyboard/mouse controls.

## Architecture

### Core Classes
1. **TaxiGame** (`source/Class/TaxiGameClass.h`)
   - Manages game state: car collection, scroll position, current tier, money
   - Handles UI: main buttons, tier buttons, car list buttons
   - Processes input: mouse movement, clicks, keyboard events
   - Key methods:
     - `initializeCars()`: Loads car data from `carslist.h`
     - `adjustScroll()`: Handles vertical scrolling with bounds checking
     - `viewAllCars()`: Renders visible cars based on current tier and scroll
     - `handleMouseMoved()`/`handleMouseClicked()`: Processes UI interactions
     - `setCurrentTier()`/`getCurrentTier()`: Manages active car category

2. **Car** (`source/Class/CarClass.h`)
   - Represents a vehicle with properties:
     - `model`: Car name (string)
     - `tier`: Service category (Economy, Comfort, etc.)
     - `capacity`: Passenger count (int)
     - `baseFare`: Per-kilometer rate (double)
     - `buyPrice`: Purchase cost (long long)
     - `owned`: Acquisition status (bool)
   - Methods:
     - `calculateFare(distance)`: Computes total fare = baseFare + (distance * 1.76)
     - Getters/setters for all properties

3. **Button** (`source/Class/ButtonClass.h`)
   - UI component with:
     - Position/size (sf::RectangleShape)
     - Label (sf::Text)
     - Hover state (color change on mouseover)
   - Methods:
     - `draw()`: Renders button to window
     - `isClicked()`: Checks if mouse coordinates are within bounds
     - `setHovered()`: Updates visual state based on hover

### Data Structure
- **Car Storage**: `vector<Car> cars` in TaxiGame class
- **Initialization**: Cars loaded in `source/carslist.h` via push_back() calls
  - Organized by tier sections (Economy, Comfort, Comfort+, Business, etc.)
  - Starter cars marked as `owned=true`, others `owned=false`
  - BuyPrice typically = baseFare * 10000 (rounded)

### UI Layers
1. **Main Menu Buttons** (`initializeMainButtons()`):
   - Exit, CarsList, CarSend, MainMenu
2. **Tier Filter Buttons** (`initializeTierButtons()`):
   - All, Economy, Comfort, Comfort+, Business, Premier, Elite, Minivan
3. **Car List**: Dynamically generated view of cars matching current tier

### Input Handling
- **Mouse**: 
  - Hover effects on buttons (color change to red)
  - Click detection for button actions
- **Keyboard**:
  - ↑/↓: Scroll car list
  - 0-8: Select tier (0=All, 1=Economy, ..., 8=Minivan)
  - Escape: Exit application
  - M: MainMenu tier
  - C: CarList tier
  - Numpad 1/3/9: Money cheat codes

### Rendering Pipeline
1. Clear window to black
2. Draw background image
3. Based on current tier:
   - "MainMenu": Show only main menu buttons
   - Other tiers: 
     - Draw scrollable car list (filtered by tier)
     - Show main menu buttons
     - Show tier filter buttons
4. Display frame

## Key Features
- **Extensive Car Database**: 200+ models from major manufacturers
- **Tiered Pricing System**: 8 service tiers with different base fares and capacities
- **Interactive UI**: Hover effects, click sounds, scrollable lists
- **Fare Calculation**: Dynamic pricing based on distance
- **Visual Polish**: Custom background, OpenSans font, 120 FPS cap
- **Audio Feedback**: Click sounds on button interactions

## File Structure
```
TaxiGame/
├── main.cpp          # Game loop and core logic
├── source/           # Header files and data
│   ├── Class/        # Core class definitions
│   │   ├── TaxiGameClass.h
│   │   ├── CarClass.h
│   │   └── ButtonClass.h
│   ├── functions/    # Helper implementations
│   │   ├── adjustScroll.h
│   │   ├── viewAllCarsFunc.h
│   │   ├── mouseClick.h
│   │   └── soundLoad.h
│   ├── carslist.h    # Vehicle database (372+ entries)
│   ├── Init.h        # Resource loading (fonts, textures, sounds)
│   ├── TierButtonsView.h
│   └── ...
├── images/           # background.jpg
├── sound/            # click.wav, start.wav, stop.wav
├── required/         # Dependencies (SFML, MinGW)
├── makefile          # Build script
└── README.md         # Project overview
```

## Build & Run (Windows)
### Prerequisites
- g++ (MinGW)
- SFML 2.5.1 (included in `required/SFML-2.5.1/`)

### Commands
```bash
make          # Builds TaxiGame.exe
./TaxiGame.exe # Run application
```

## Controls Summary
| Input | Action |
|-------|--------|
| Mouse | Hover/click buttons |
| ↑/↓ | Scroll car list |
| 0-8 | Select tier (0=All, 1=Economy, 2=Comfort, 3=Comfort+, 4=Business, 5=Cruise, 6=Premier, 7=Elite, 8=Minivan) |
| Escape | Exit application |
| M | Switch to MainMenu tier |
| C | Switch to CarList tier |
| Numpad 3 | +$10,000 money |
| Numpad 9 | +$100,000 money |
| Numpad 1 | -$100,000 money |

## Car Tier System
| Tier | Base Fare | Capacity | Example Vehicles |
|------|-----------|----------|------------------|
| Economy | $1.49/km | 4 | BMW 3er, Hyundai Solaris |
| Comfort | $1.69/km | 4 | Audi A6, Kia K5 |
| Comfort+ | $3.50/km | 4 | BMW 5er, Genesis G80 |
| Business | $10/km | 3 | Audi A8, Mercedes S-Class |
| Cruise | $12/km | 6 | Mercedes V-Class |
| Premier | $15/km | 3-6 | Rolls Royce Ghost |
| Elite | $20/km | 3-6 | Bentley Flying Spur |
| Minivan | $7/km | 6 | Kia Carnival |

## Notes
- Car list scrolls vertically with bounds checking per tier
- Owned cars appear first in each tier section (marked in carslist.h)
- BuyPrice calculation: baseFare * 10000 (rounded to nearest integer)
- Sound effects require corresponding .wav files in sound/ directory
- Background image: images/background.jpg
- Font: OpenSans-Italic-VariableFont_wdth,wght.ttf

## Future Enhancements (from TODO)
- Implement full CarSend feature
- Add distance input & real-time fare calculation UI
- Add car images per model
- Polish UI/UX