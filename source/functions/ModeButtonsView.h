void TaxiGame::viewModeButtons(sf::RenderWindow& app, sf::Font& font) {// Получение позиции мыши и рендер кнопок уровней (правая панель)
sf::Vector2i mousePos = sf::Mouse::getPosition(app);
for (auto& button : getModeButtons()) {
        button.draw(app);
    }
}
