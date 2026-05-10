void TaxiGame::viewManufacturerButtons(sf::RenderWindow& app, sf::Font& font) {
    for (auto& button : manufacturerbuttons) {
        button.draw(app);
    }
}