void TaxiGame::viewMainMenuButtons(sf::RenderWindow& app, sf::Font& font) {
    for (auto& button : getMainButtons()) {
        button.draw(app);
    }
}