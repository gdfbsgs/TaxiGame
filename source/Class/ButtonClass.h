// Класс Button для UI-элементов - кнопки с SFML графикой, hover-эффектом и детекцией клика
class Button {

private:
    // Прямоугольник кнопки
    sf::RectangleShape shape;
    // Текст на кнопке
    sf::Text text;
    // Надпись кнопки
    std::string label;

    
public:
    // Конструктор кнопки: позиция, размер, текст, шрифт. Синий цвет, белый текст, центрирование
    Button(float x, float y, float width, float height, const std::string& text_label, sf::Font& font) : label(text_label) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color(0, 0, 128));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(0, 0, 170));

        
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        
        // Center text in button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (width - textBounds.width) / 2,
            y + (height - textBounds.height) / 2 - 5
        );
    }
    
    // Рисование кнопки на экране
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);
    }

    
    // Проверка клика по кнопке координатами мыши
    bool isClicked(float mouseX, float mouseY) const {
        return shape.getGlobalBounds().contains(mouseX, mouseY);
    }

    
    // Установка hover-эффекта: красный при наведении
    void setHovered(bool hovered) {
        if(hovered){
            shape.setFillColor(sf::Color::Red);
        } 
        else{
            shape.setFillColor(sf::Color(0, 0, 128));
        }
    }

    
    const std::string& getLabel() const {
        return label;
    }
};