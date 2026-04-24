// Размеры окна игры 1000x1000 пикселей
int ScreenWidth = 1000, ScreenHeight = 1000;

    // Initialize window
    // Создание главного окна игры
    sf::RenderWindow app(sf::VideoMode(ScreenWidth, ScreenHeight), "TaxiGame");
    app.setFramerateLimit(120); // Ограничение FPS 120

    // Load font
    // Загрузка шрифта для текста кнопок и UI
    sf::Font font;
    font.loadFromFile("OpenSans-Italic-VariableFont_wdth,wght.ttf");

    // Загрузка фона
    sf::Texture t1;
    t1.loadFromFile("images/background.jpg");
    #include "soundLoad.h" // Загрузка звуков
    sf::Sprite Background(t1);

    // Initialize game
    // Создание и инициализация игры: главные кнопки, кнопки уровней, старт с MainMenu, проигрыш стартового звука
    TaxiGame game;
    game.setCurrentTier("Economy"); 
    game.setCurrentMode("YandexGo");
    game.initializeMainButtons(font); 
    game.initializeTierButtons(font);
    game.initializeModeButtons(font);
    game.gameFont = &font;
    
    sound2.play();