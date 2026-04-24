// Главный класс игры TaxiGame - управляет списком машин, UI-кнопками, прокруткой и состояниями уровней
class TaxiGame {

    private:
        // Список всех доступных такси-машин
        vector<Car> cars;

        
        // Вертикальная прокрутка списка машин
        long long scrollY;
        // Текущий фильтр уровня (Economy, Comfort и т.д.)
        string currentTier;
        string currentMode = "YandexGo";
        int selectedCarIndex = 0;
        string distanceInput = "";
        long long computedFee = 0;
        
        // Общий список кнопок (используется редко)
        vector<Button> buttons; 
        // Кнопки уровней (Economy, Comfort...)
        vector<Button> tierButtons;
        // Главные кнопки меню (Exit, MainMenu...)
        vector<Button> mainButtons;
        vector<Button> modeButtons;


        // Приватный метод загрузки списка машин
        void initializeCars();

    public: 
        // Геттер списка машин (для рендера)
        vector<Car>& getCars() {
            return cars;
        }

        long long money;
        sf::Font* gameFont = nullptr;
    
        // Конструктор: стартовые ~USD под реалистичные цены авто; прокрутка 0, уровень "All"
        TaxiGame() : money(65000), currentTier("All") {
            initializeCars();
        }




        // Рендер списка машин с кнопками покупки (основной вид)
        void viewAllCars(sf::RenderWindow& app, sf::Font& font, sf::Vector2i mousePos);

        void viewAllTiers();



        // Инициализация главных кнопок меню
        void initializeMainButtons(sf::Font& font);
        void initializeTierButtons(sf::Font& font);
        void initializeModeButtons(sf::Font& font);

        void viewMainMenuButtons(sf::RenderWindow& app, sf::Font& font);
        void viewTierButtons(sf::RenderWindow& app, sf::Font& font);
        void viewModeButtons(sf::RenderWindow& app, sf::Font& font);
        int getCarsCount();
        
        void setCurrentTier(string t);
        string getCurrentTier();
        vector<Button>& getButtons();
        void addButton(float x, float y, float width, float height, const string& label, sf::Font& font);
       
        
        // Геттер кнопок уровней
        vector<Button>& getTierButtons() { 
            return tierButtons;
        }
        // Геттер главных кнопок
        vector<Button>& getMainButtons() { 
            return mainButtons;
        }
        vector<Button>& getModeButtons() { 
            return modeButtons;
        }
        // Обработка движения мыши (hover кнопок)
        void handleMouseMoved(sf::Vector2i mousePos);
        // Обработка клика мыши (действия кнопок)
        void handleMouseClicked(sf::Vector2i mousePos, sf::RenderWindow& app);
        void setCurrentMode(string m);
        string getCurrentMode();
   
        void viewCarSend(sf::RenderWindow& app, sf::Font& font);
        void handleKeyInput(sf::Event::KeyEvent key);
};

