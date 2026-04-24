void TaxiGame::viewTierButtons(sf::RenderWindow& app, sf::Font& font) {
sf::Vector2i mousePos = sf::Mouse::getPosition(app);
for (auto& button : getTierButtons()) {
        button.draw(app);
    }
}
