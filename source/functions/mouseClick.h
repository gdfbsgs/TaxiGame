// Метод обработки клика мыши по кнопкам: главные кнопки и кнопки уровней
void TaxiGame::handleMouseClicked(sf::Vector2i mousePos, sf::RenderWindow& app) {

    // Handle main buttons
    // Обработка кликов по главным кнопкам меню
    for (auto& button : mainButtons) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            string label = button.getLabel();
            if (label == "Exit") {
                app.close();
            }
            if (label == "CarsList") {
                setCurrentTier("Economy");
            }
            if (label == "MainMenu") {
                setCurrentTier("MainMenu");
            }
            if (label == "ModeSelect") {
                setCurrentTier("ModeSelect");
            }
            if (label == "CarSend") {
                setCurrentTier("CarSend");
            }
        }
    }

    // Handle tier buttons
    // Обработка кликов по кнопкам уровней (переключение фильтра машин)
    for (auto& button : tierButtons) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            setCurrentTier(button.getLabel());
        }
    }
    for (auto& button : modeButtons) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            if(button.getLabel() == "Bolt") {
                setCurrentTier("CarSend");
            } 
            else {
                setCurrentMode(button.getLabel());
            }
        }
    }
    // Handle color buttons
    for (auto& button : colorbuttons) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            setCurrentColor(button.getLabel());
        }
    }
    // Handle manufacturer buttons
    for (auto& button : manufacturerbuttons) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            if(button.getLabel() == "Other") {
                setCurrentManufacturer("All");
            } 
            else {
            setCurrentManufacturer(button.getLabel());
            
        }
    }
}

