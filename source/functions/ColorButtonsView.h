void TaxiGame::viewColorButtons(sf::RenderWindow& app, sf::Font& font) {
    for (auto& button : colorbuttons) {
        button.draw(app);
    }
}