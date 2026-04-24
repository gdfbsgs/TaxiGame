void TaxiGame::handleMouseMoved(sf::Vector2i mousePos) {
    for (auto& button : mainButtons) {
        button.setHovered(button.isClicked(mousePos.x, mousePos.y));
    }
    for (auto& button : tierButtons) {
        button.setHovered(button.isClicked(mousePos.x, mousePos.y));
    }
    for (auto& button : modeButtons) {
        button.setHovered(button.isClicked(mousePos.x, mousePos.y));
    }
}