#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <SFML/Window.hpp>  // SFML для окна и событий
#include <SFML/Graphics.hpp> // SFML для графики (спрайты, текст, фигуры)
#include <SFML/Audio.hpp>   // SFML для звука
#include <time.h>
#include <random> 
using namespace std;
#include "source/Class/CarClass.h"     // Класс машины (такси)
#include "source/Class/ButtonClass.h"   // Класс кнопки UI
#include "source/Class/TaxiGameClass.h" // Главный класс игры
#include "source/Class/RideClass.h"     // Класс ride (заказ)
#include "source/Class/RideSystemClass.h" // Система управления заказами
#include "source/functions/RidesView.h" // UI для отображения заказов
// Set to false to completely disable the ride system
const bool RIDES_ENABLED = true;
int TaxiGame::getCarsCount() {
    return cars.size();
}
string TaxiGame::getCurrentMode() {
    return currentMode;
}
void TaxiGame::setCurrentMode(string m) {
    currentMode = m;
    tierButtons.clear();
    manufacturerbuttons.clear();
    if (gameFont != nullptr) {
        initializeTierButtons(*gameFont);
        initializeManufacturerButtons(*gameFont);
    }
    // Validate currentTier against the newly created buttons
    if (currentTier != "MainMenu" && currentTier != "ModeSelect") {
        bool valid = false;
        for (auto& button : tierButtons) {
            if (button.getLabel() == currentTier) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            currentTier = "All";
        }
    }
}
void TaxiGame::setCurrentTier(string t) {
    currentTier = t;
}
//текущего уровня
string TaxiGame::getCurrentTier() {
    return currentTier;
}
void TaxiGame::setCurrentColor(string c) {
    currentColor = c;
}
string TaxiGame::getCurrentColor() {
    return currentColor;
}
void TaxiGame::setCurrentManufacturer(string m) {
    currentManufacturer = m;
}
string TaxiGame::getCurrentManufacturer() {
    return currentManufacturer;
}
vector<Button>& TaxiGame::getButtons() {
    return buttons;
} 
// CARS LIST
void TaxiGame::initializeCars() {
    #include "source/carslist.h"
    
}
#include "source/functions/ButtonAdd.h"
#include "source/viewAllCarsFunc.h" 


#include "source/TierButtonsInit.h"
#include "source/ColorButtonsInit.h"
#include "source/ModeButtonsInit.h"
#include "source/ManufacturerButtonsInit.h"
#include "source/MainMenuButtonsInit.h"

#include "source/functions/MainMenuButtonsView.h"
#include "source/functions/TierButtonsView.h"
#include "source/functions/ModeButtonsView.h"
#include "source/functions/ColorButtonsView.h"
#include "source/functions/ManufacturerButtonsView.h"
#include "source/functions/mouseMove.h"
#include "source/functions/mouseClick.h"
#include "source/CarSendWindow.h"

int main() {
    #include "source/GameStart.h"
    
    // Initialize Ride System (can be disabled by setting RIDES_ENABLED to false)
    RideSystem rideSystem;
    if (RIDES_ENABLED) {
        rideSystem.setRideGenerationChance(0.15f); // 15% chance to generate ride each frame
    }
    
    while (app.isOpen()){ // кнопка закрыть приложение
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                sound3.play();
                
                app.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                game.handleMouseMoved(mousePos);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                    // Always check main menu buttons first (Exit, CarsList, MainMenu, ModeSelect, CarSend)
                    bool mainButtonClicked = false;
                    for (auto& button : game.getMainButtons()) {
                        if (button.isClicked(mousePos.x, mousePos.y)) {
                            mainButtonClicked = true;
                            break;
                        }
                    }
                    
                    if (mainButtonClicked) {
                        game.handleMouseClicked(mousePos, app);
                    } else if (game.getCurrentTier() == "CarSend") {
                        // Only handle CarSend-specific clicks if not a main button
                        handleCarSendClick(mousePos, game);
                    } else {
                        // Handle other clicks normally
                        game.handleMouseClicked(mousePos, app);
                    }
                    sound.play();
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    game.setCurrentTier("MainMenu");
                } 
                if (event.key.code == sf::Keyboard::C) {
                    game.setCurrentTier("CarList");
                } 
                if (event.key.code == sf::Keyboard::Num3) {
                    game.money += 10000;
                } 
                if (event.key.code == sf::Keyboard::Num9) {
                    game.money += 100000;
                } 
                if (event.key.code == sf::Keyboard::Num1) {
                    game.money -= 100000;
                }
                // ===== RIDE SYSTEM KEYBOARD HANDLERS =====
                if (RIDES_ENABLED) {
                    // Accept ride with SPACE + 0-4 (for rides 0-4)
                    if (event.key.code == sf::Keyboard::Space) {
                        // This will be handled with number keys below
                    }
                    // Number keys 0-4 to accept rides
                    if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num4) {
                        int rideIndex = event.key.code - sf::Keyboard::Num0;
                        if (rideSystem.acceptRide(rideIndex)) {
                            game.money += rideSystem.completeRide(rideIndex) / 2; // Partial payment on acceptance
                        }
                    }
                    // R key to toggle/reset ride system
                    if (event.key.code == sf::Keyboard::R) {
                        rideSystem.clearRides();
                    }
                }
                // =========================================
                if (event.key.code == sf::Keyboard::Escape) {
                    sound3.play();
                    app.close();
                }
        }
        if(game.getCurrentTier() == "CarSend"){
            app.clear(sf::Color::Black);
            app.draw(Background);
            // carSendDistance = (rand() % 50) + 5;
            // if (carSendSelectedTier.empty()) {
            //     openCarSendUI(game.getCurrentMode(), font);
            // }
            // viewCarSendUI(app, game);
            game.viewMainMenuButtons(app, font);
            sf::Text Not_available;
            Not_available.setFont(font);
            Not_available.setString("In Progress...");
            Not_available.setCharacterSize(50);
            Not_available.setFillColor(sf::Color::Red);
            Not_available.setPosition(400.f, 500.f);
            app.draw(Not_available);
            // ====================================================
            
            app.display();
        }
        else if (game.getCurrentTier() == "MainMenu") {
            app.clear(sf::Color::Black);
            app.draw(Background);
            game.viewMainMenuButtons(app, font);
            app.display();
        }
         
        else if(game.getCurrentTier() == "ModeSelect"){
            app.clear(sf::Color::Black);
            app.draw(Background);
            game.viewMainMenuButtons(app, font);
            game.viewModeButtons(app, font);
            app.display();
        }
        else if(game.getCurrentTier() != "MainMenu" and game.getCurrentTier() != "ModeSelect" and game.getCurrentTier() != "CarSend"){
            app.clear(sf::Color::Black);
            app.draw(Background);
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            game.viewMainMenuButtons(app, font);
            game.viewManufacturerButtons(app, font);
            game.viewAllCars(app, font, mousePos, game);
            app.display();
        } 
        
    }
}

}
