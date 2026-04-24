void TaxiGame::addButton(float x, float y, float width, float height, const string& label, sf::Font& font) {
    buttons.emplace_back(x, y, width, height, label, font);
}