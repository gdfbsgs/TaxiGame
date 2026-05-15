void TaxiGame::viewAllCars(sf::RenderWindow& app, sf::Font& font, sf::Vector2i mousePos, TaxiGame& game) {
    // Initialize manufacturer buttons if not already
    if (manufacturerbuttons.empty()) {
        initializeManufacturerButtons(font);
    }
    // Локальные переменные для текста: уровень, деньги, машины
    sf::Text tierText;
    sf::Text moneyText;
    sf::Text carModelText;
    sf::Text carInfoText;
    sf::Text carManufacturerText;
    // Текущий отображаемый автомобиль (статический, чтобы сохранять между кадрами)
    static long long carCurrent = 0;
    static std::string prevColor = "";
    static std::string prevManufacturer = "";
    static int debounce = 0; // Frame debounce instead of sleep
    static sf::Texture carTexture;
    static std::string lastModel = "";
    
    std::string currentTier = getCurrentTier();
    std::string currentColor = getCurrentColor();
    std::string currentManufacturer = getCurrentManufacturer();
    
    // Detect color or manufacturer change or invalid, reset to first matching
    if (currentColor != prevColor || currentManufacturer != prevManufacturer || cars.empty() || carCurrent < 0 || carCurrent >= cars.size() || (currentColor != "All" && cars[carCurrent].getColor() != currentColor) || (currentManufacturer != "All" && cars[carCurrent].getManufacturer() != currentManufacturer)) {
        carCurrent = 0;
        // Find first matching
        while (carCurrent < cars.size() && ((currentColor != "All" && cars[carCurrent].getColor() != currentColor) || (currentManufacturer != "All" && cars[carCurrent].getManufacturer() != currentManufacturer))) {
            carCurrent++;
        }
        prevColor = currentColor;
        prevManufacturer = currentManufacturer;
    }
    
    // Keyboard navigation with debounce
    if (debounce <= 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (carCurrent > 0){
                carCurrent--;
                while(carCurrent > 0 && ((currentColor != "All" && cars[carCurrent].getColor() != currentColor) || (currentManufacturer != "All" && cars[carCurrent].getManufacturer() != currentManufacturer))){
                    carCurrent--;
                }
            }
            debounce = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            carCurrent++;
            while(carCurrent < cars.size() && ((currentColor != "All" && cars[carCurrent].getColor() != currentColor) || (currentManufacturer != "All" && cars[carCurrent].getManufacturer() != currentManufacturer))){
                carCurrent++;
            }
            if (carCurrent >= cars.size()) {
                carCurrent = 0;
                // Find first matching on wrap
                while (carCurrent < cars.size() && ((currentColor != "All" && cars[carCurrent].getColor() != currentColor) || (currentManufacturer != "All" && cars[carCurrent].getManufacturer() != currentManufacturer))) {
                    carCurrent++;
                }
            }
            debounce = 1;
        }
    } else {
        debounce--;
    }
    
    // Draw car if valid
    if (carCurrent >= 0 && carCurrent < cars.size() && (currentColor == "All" || cars[carCurrent].getColor() == currentColor) && (currentManufacturer == "All" || cars[carCurrent].getManufacturer() == currentManufacturer)) {
        // Cache texture
        std::string model = cars[carCurrent].getModel();
        std::string manufacturer = cars[carCurrent].getManufacturer();
        if (model != lastModel || carTexture.getSize() == sf::Vector2u(0,0)) {
            if(!carTexture.loadFromFile("source/Car Images/" + manufacturer + "/" + model + ".png")){
                carTexture.loadFromFile("source/Car Images/DEFAULT.png");
            }
            lastModel = model;
        }
        sf::Sprite carSprite(carTexture);
        carSprite.setScale(1, 1);
        carSprite.setPosition(180.f, 160.f);
        app.draw(carSprite);
        
        carModelText.setFont(font);
        carModelText.setString(model + (cars[carCurrent].getVariant().empty() ? "" : " " + cars[carCurrent].getVariant()));
        carModelText.setCharacterSize(28);
        carModelText.setFillColor(sf::Color::Blue);
        carModelText.setPosition(50.f, 580.f);
        app.draw(carModelText);

        carManufacturerText.setFont(font);
        carManufacturerText.setString("Manufacturer: " + cars[carCurrent].getManufacturer());
        carManufacturerText.setCharacterSize(28);
        carManufacturerText.setFillColor(sf::Color::Blue);
        carManufacturerText.setPosition(50.f, 710.f);
        app.draw(carManufacturerText);
        sf::Text CarQuant;
        CarQuant.setFont(font);
        long long qw = cars[carCurrent].getQuantity(); 
        CarQuant.setString("Quantity:" + std::to_string(qw));
        CarQuant.setCharacterSize(28);
        CarQuant.setFillColor(sf::Color::Blue);
        CarQuant.setPosition(50.f, 670.f);
        app.draw(CarQuant);

        carInfoText.setFont(font);
        std::string tierCar = cars[carCurrent].getTier();
        long long price = cars[carCurrent].getBuyPrice();
        std::string ownedStr;
        if(cars[carCurrent].isOwned()){
            ownedStr = "OWNED";
        }
        else{
            ownedStr ="[$" + std::to_string(price) + "]";
        }
        
        carInfoText.setString("Supported: " + cars[carCurrent].getMode() + " - " + tierCar + "   " + ownedStr);
        carInfoText.setCharacterSize(22);
        if(cars[carCurrent].isOwned()){
            carInfoText.setFillColor(sf::Color::Blue);
        }
        else{
            carInfoText.setFillColor(sf::Color::Blue);
        }
        
        carInfoText.setPosition(50.f, 620.f);
        app.draw(carInfoText); 
        // Кнопка BUY (если машина не куплена и достаточно денег)
        if (!cars[carCurrent].isOwned() or cars[carCurrent].isOwned()) {
            sf::Vector2i localMousePos = sf::Mouse::getPosition(app);
            sf::FloatRect buyRect(650.f, 650.f, 120.f, 50.f);
            bool canBuy = money >= cars[carCurrent].getBuyPrice();
            
            if (canBuy && sf::Mouse::isButtonPressed(sf::Mouse::Left) && buyRect.contains(localMousePos.x, localMousePos.y)) {
                money -= cars[carCurrent].getBuyPrice();
                //cars[carCurrent].setOwned(true);
                long long quant = cars[carCurrent].getQuantity();
                cars[carCurrent].setQuantity(quant + 1);
            }
            
            sf::RectangleShape buyBox(sf::Vector2f(120.f, 50.f));
            buyBox.setPosition(750.f, 750.f);
            buyBox.setFillColor(canBuy ? sf::Color::Green : sf::Color::Red);
            buyBox.setOutlineThickness(2);
            buyBox.setOutlineColor(sf::Color::White);
            app.draw(buyBox);
            
            sf::Text buyText;
            buyText.setFont(font);
            buyText.setString("BUY");
            buyText.setCharacterSize(24);
            buyText.setFillColor(sf::Color::White);
            buyText.setPosition(780.f, 760.f); // центрируем примерно
            app.draw(buyText);
        }
    } else {
        // No cars message
        sf::Text noCarsText;
        noCarsText.setFont(font);
        noCarsText.setString("No cars for tier: " + currentTier);
        noCarsText.setCharacterSize(48);
        noCarsText.setFillColor(sf::Color::Red);
        noCarsText.setPosition(300.f, 400.f);
        app.draw(noCarsText);
    }
    
    
    sf::Text manufacturerText;
    manufacturerText.setFont(font);
    manufacturerText.setString("Manufacturer: " + getCurrentManufacturer());
    manufacturerText.setCharacterSize(25);
    manufacturerText.setFillColor(sf::Color::Blue);
    manufacturerText.setPosition(620.f, 3.f);
    app.draw(manufacturerText);
    
    moneyText.setFont(font);
    moneyText.setString("Money: " + std::to_string(money));
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::Blue);
    moneyText.setPosition(620.f, 35.f);
    app.draw(moneyText);`
    sf::Text Modetext;
    Modetext.setFont(font);
    Modetext.setString("Mode: " + getCurrentMode());
    Modetext.setCharacterSize(20);
    Modetext.setFillColor(sf::Color::Blue);
    Modetext.setPosition(620.f, 70.f);
    app.draw(Modetext);

    sf::Text colorText;
    colorText.setFont(font);
    colorText.setString("Color: " + getCurrentColor());
    colorText.setCharacterSize(20);
    colorText.setFillColor(sf::Color::Blue);
    colorText.setPosition(620.f, 105.f);
    app.draw(colorText);
    
    for (auto& button : colorbuttons) {
        button.draw(app);
    }
    for (auto& button : manufacturerbuttons) {
        button.draw(app);
    }
}

