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

// Метод регулировки вертикальной прокрутки списка машин (на стрелки вверх/вниз)
// Возвращает количество доступных машин
int TaxiGame::getCarsCount() {
    return cars.size();
}
string TaxiGame::getCurrentMode() {
    return currentMode;
}
void TaxiGame::setCurrentMode(string m) {
    currentMode = m;
    tierButtons.clear();
    if (gameFont != nullptr) {
        initializeTierButtons(*gameFont);
    }
    // Validate currentTier against the newly created buttons
    if (currentTier != "MainMenu" && currentTier != "ModeSelect") {
        bool valid = false;
        for (const auto& button : tierButtons) {
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
#include "source/ModeButtonsInit.h"
#include "source/MainMenuButtonsInit.h"

#include "source/functions/MainMenuButtonsView.h"
#include "source/functions/TierButtonsView.h"
#include "source/functions/ModeButtonsView.h"

#include "source/functions/mouseMove.h"
#include "source/functions/mouseClick.h"
int main() {
    #include "source/GameStart.h"
    
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
                    game.handleMouseClicked(mousePos, app);
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
                if (event.key.code == sf::Keyboard::Escape) {
                    sound3.play();
                    app.close();
                }
        }
        // Рендер в зависимости от текущего уровня (MainMenu или список машин)
        if (game.getCurrentTier() == "MainMenu") {
            app.clear(sf::Color::Black);
            app.draw(Background);
            game.viewMainMenuButtons(app, font);
            app.display();
        }
         
        if(game.getCurrentTier() == "ModeSelect"){
            app.clear(sf::Color::Black);
            app.draw(Background);
            game.viewMainMenuButtons(app, font);
            game.viewModeButtons(app, font);
            app.display();
        }
        if(game.getCurrentTier() == "CarSend"){
            game.money += 10000;
            game.setCurrentTier("All");
        }
        if(game.getCurrentTier() != "MainMenu" and game.getCurrentTier() != "ModeSelect" and game.getCurrentTier() != "CarSend"){
            app.clear(sf::Color::Black);
            app.draw(Background);
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            game.viewAllCars(app, font, mousePos);
            game.viewMainMenuButtons(app, font);
            game.viewTierButtons(app, font);
            app.display();
        } 
        
    }
}

}
