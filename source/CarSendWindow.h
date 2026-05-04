// CarSendWindow - renders within main window when tier == "CarSend"

// UI elements
sf::Text carSendTitle;
sf::Text distanceDisplayText;
sf::Text selectedTierDisplay;
sf::Text earningsDisplay;

std::string carSendSelectedTier = "";
int carSendDistance = 0;
Button* carSendConfirmbutton = nullptr;
Button* carSendCancelbutton = nullptr;

void openCarSendUI(std::string currentMode, sf::Font& font) {
    // Setup UI elements
    carSendTitle.setFont(font);
    distanceDisplayText.setFont(font);
    selectedTierDisplay.setFont(font);
    earningsDisplay.setFont(font);
    carSendTitle.setCharacterSize(28);
    selectedTierDisplay.setCharacterSize(20);
    earningsDisplay.setCharacterSize(20);
    distanceDisplayText.setCharacterSize(24);
    carSendTitle.setString("Send Car");
    
    carSendTitle.setFillColor(sf::Color::White);
    carSendTitle.setPosition(200, 50);
    
    
    
    selectedTierDisplay.setFillColor(sf::Color::Cyan);
    earningsDisplay.setFillColor(sf::Color::Green);
    selectedTierDisplay.setPosition(100, 210);
    earningsDisplay.setPosition(100, 260);
    
    distanceDisplayText.setFillColor(sf::Color::Yellow);
    distanceDisplayText.setPosition(150, 120);
    
    // Reset values
    carSendSelectedTier = "";
    
    distanceDisplayText.setString("Distance: " + std::to_string(carSendDistance) + " km");
    selectedTierDisplay.setString("Selected Tier: None");
    earningsDisplay.setString("Estimated Earnings: $0");
    
    // Create buttons
    if (carSendConfirmbutton != nullptr){
        delete carSendConfirmbutton;
    }
    if (carSendCancelbutton != nullptr){
        delete carSendCancelbutton;
    }
    carSendConfirmbutton = new Button(200, 800, 150, 50, "CONFIRM", font);
    carSendCancelbutton = new Button(650, 800, 150, 50, "CANCEL", font);
}

float getCarSendEarnings(const std::string& tier, int distance) {
    if (tier.empty() || distance == 0){
        return 0;
    }
    float baseRate = 10.0f;
    float tierMultiplier = 1.0f;
    
    // Uber multipliers
    if (tier == "UberX") tierMultiplier = 1.0f;
    else if (tier == "UberXL") tierMultiplier = 1.5f;
    else if (tier == "Black") tierMultiplier = 2.0f;
    else if (tier == "Electric") tierMultiplier = 1.3f;
    else if (tier == "VanXL") tierMultiplier = 1.8f;
    
    // YandexGo multipliers
    else if (tier == "Economy") tierMultiplier = 1.0f;
    else if (tier == "Comfort") tierMultiplier = 1.2f;
    else if (tier == "Comfort+") tierMultiplier = 1.5f;
    else if (tier == "Business") tierMultiplier = 1.8f;
    else if (tier == "Elite") tierMultiplier = 2.2f;
    else if (tier == "Cruise") tierMultiplier = 1.6f;
    else if (tier == "Premier") tierMultiplier = 2.0f;
    else if (tier == "Minivan") tierMultiplier = 2.3f;
    
    return baseRate * distance * tierMultiplier;
}

void handleCarSendClick(sf::Vector2i mousePos, TaxiGame& game) {
    // Tier button clicks (use existing tier buttons)
    for (auto& button : game.getTierButtons()) {
        if (button.isClicked(mousePos.x, mousePos.y)) {
            carSendSelectedTier = button.getLabel();
            int earnings = (int)getCarSendEarnings(carSendSelectedTier, carSendDistance);
            selectedTierDisplay.setString("Selected Tier: " + carSendSelectedTier);
            earningsDisplay.setString("Estimated Earnings: $" + std::to_string(earnings));
            return;
        }
    }
    
    // Confirm button
    if (carSendConfirmbutton != nullptr && carSendConfirmbutton->isClicked(mousePos.x, mousePos.y) && !carSendSelectedTier.empty()) {
        game.money += (int)getCarSendEarnings(carSendSelectedTier, carSendDistance);
        game.setCurrentTier("All");
        return;
    }
    
    // Cancel button
    if (carSendCancelbutton != nullptr && carSendCancelbutton->isClicked(mousePos.x, mousePos.y)) {
        game.setCurrentTier("All");
        return;
    }
}

void viewCarSendUI(sf::RenderWindow& app, TaxiGame& game) {
    app.draw(carSendTitle);
    app.draw(distanceDisplayText);
    app.draw(selectedTierDisplay);
    app.draw(earningsDisplay);
    
    for (auto& button : game.getTierButtons()) {
        if (button.getLabel() == carSendSelectedTier) {
            button.setHovered(true);
        } else {
            button.setHovered(false);
        }
        button.draw(app);
    }
    
    if (carSendConfirmbutton != nullptr) carSendConfirmbutton->draw(app);
    if (carSendCancelbutton != nullptr) carSendCancelbutton->draw(app);
}
