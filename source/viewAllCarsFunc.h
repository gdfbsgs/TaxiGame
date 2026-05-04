void TaxiGame::viewAllCars(sf::RenderWindow& app, sf::Font& font, sf::Vector2i mousePos) {
    // Локальные переменные для текста: уровень, деньги, машины
    sf::Text tierText;
    sf::Text moneyText;
    sf::Text carModelText;
    sf::Text carInfoText;
    
    // Текущий отображаемый автомобиль (статический, чтобы сохранять между кадрами)
    static long long carCurrent = 0;
    static std::string prevTier = "";
    static int debounce = 0; // Frame debounce instead of sleep
    static sf::Texture carTexture;
    static std::string lastModel = "";
    
    std::string currentTier = getCurrentTier();
    
    // Detect tier change or invalid, reset to first matching
    if (currentTier != prevTier || cars.empty() || carCurrent < 0 || carCurrent >= cars.size() || cars[carCurrent].getTier() != currentTier) {
        carCurrent = 0;
        // Find first matching
        while (carCurrent < cars.size() && (currentTier != "All" && cars[carCurrent].getTier() != currentTier)) {
            carCurrent++;
        }
        prevTier = currentTier;
    }
    
    // Keyboard navigation with debounce
    if (debounce <= 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (carCurrent > 0){
                carCurrent--;
                while(carCurrent > 0 && (currentTier != "All" && cars[carCurrent].getTier() != currentTier)){
                    carCurrent--;
                }
            }
            debounce = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            carCurrent++;
            while(carCurrent < cars.size() && (currentTier != "All" && cars[carCurrent].getTier() != currentTier)){
                carCurrent++;
            }
            if (carCurrent >= cars.size()) {
                carCurrent = cars.size();
                // Find first matching on wrap
                while (carCurrent < cars.size() && (currentTier != "All" && cars[carCurrent].getTier() != currentTier)) {
                    carCurrent++;
                }
            }
            debounce = 1;
        }
    } else {
        debounce--;
    }
    
    // Draw car if valid
    if (carCurrent >= 0 && carCurrent < cars.size() && (currentTier == "All" or currentTier == "UberX" || cars[carCurrent].getTier() == currentTier)) {
        // Cache texture
        std::string model = cars[carCurrent].getModel();
        if (model != lastModel || carTexture.getSize() == sf::Vector2u(0,0)) {
            if(!carTexture.loadFromFile("source/Car Images/" + model + ".png")){
                carTexture.loadFromFile("source/Car Images/DEFAULT.png");
            }
            lastModel = model;
        }
        sf::Sprite carSprite(carTexture);
        carSprite.setScale(1, 1);
        carSprite.setPosition(250.f, 220.f);
        app.draw(carSprite);
        
        carModelText.setFont(font);
        carModelText.setString(model);
        carModelText.setCharacterSize(28);
        carModelText.setFillColor(sf::Color::Blue);
        carModelText.setPosition(50.f, 580.f);
        app.draw(carModelText);
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
        
        carInfoText.setString("Tier: " + tierCar + "   " + ownedStr);
        carInfoText.setCharacterSize(20);
        if(cars[carCurrent].isOwned()){
            carInfoText.setFillColor(sf::Color::Green);
        }
        else{
            carInfoText.setFillColor(sf::Color::Red);
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
            buyBox.setPosition(650.f, 650.f);
            buyBox.setFillColor(canBuy ? sf::Color::Green : sf::Color::Red);
            buyBox.setOutlineThickness(2);
            buyBox.setOutlineColor(sf::Color::White);
            app.draw(buyBox);
            
            sf::Text buyText;
            buyText.setFont(font);
            buyText.setString("BUY");
            buyText.setCharacterSize(24);
            buyText.setFillColor(sf::Color::White);
            buyText.setPosition(680.f, 660.f); // центрируем примерно
            app.draw(buyText);
        }
    } else {
        // No cars message
        sf::Text noCarsText;
        noCarsText.setFont(font);
        noCarsText.setString("No cars for tier: " + currentTier);
        noCarsText.setCharacterSize(24);
        noCarsText.setFillColor(sf::Color::Yellow);
        noCarsText.setPosition(50.f, 400.f);
        app.draw(noCarsText);
    }
    
    
    tierText.setFont(font);
    tierText.setString("Tier: " + getCurrentTier());
    tierText.setCharacterSize(25);
    tierText.setFillColor(sf::Color::Blue);
    tierText.setPosition(640.f, 3.f);
    app.draw(tierText);
    
    moneyText.setFont(font);
    moneyText.setString("Money: " + std::to_string(money));
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::Blue);
    moneyText.setPosition(640.f, 35.f);
    app.draw(moneyText);
    sf::Text Modetext;
    Modetext.setFont(font);
    Modetext.setString("Mode: " + getCurrentMode());
    Modetext.setCharacterSize(20);
    Modetext.setFillColor(sf::Color::Blue);
    Modetext.setPosition(640.f, 70.f);
    app.draw(Modetext);
              
}

