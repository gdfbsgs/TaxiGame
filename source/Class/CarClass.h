// Класс Car представляет модель такси-машины с характеристиками: модель, уровень, вместимость, тариф, цена покупки, владение
class Car {

private:
    // Название модели машины
    std::string model;
    // Уровень (Economy, Comfort...)
    std::string tier;
    std::string manufacturer;
    std::string color;
    std::string variant;
    std::string mode;
    // Вместимость пассажиров
    long long capacity;
    // Базовый тариф за км
    float baseFare;
    // Цена покупки
    long long buyPrice;
    // Владеет ли игрок
    bool owned;
    // Количество машин этой модели в парке (для такси-флота)
    long long quantity;


public:
    // Конструктор: модель, вместимость, тариф, класс, цена, владение, количество, вариант, режим (по умолчанию "YandexGo")
    Car(std::string m,std::string manu, std::string col, long long c, double bf, std::string t, double bp = 0.0, bool o = false, long long qty = 1, std::string v = "", std::string mde = "YandexGo")
        : model(m), manufacturer(manu), color(col), capacity(c), baseFare(bf), tier(t), buyPrice(bp), owned(o), quantity(qty), variant(v), mode(mde) {}


    std::string getModel() const {
        return model;
    }
    std::string getTier() const { 
        return tier; 
    }
    std::string getManufacturer() const { 
        return manufacturer; 
    }
    std::string getColor() const {
        return color;
    }
    std::string getVariant() const {
        return variant;
    }
    std::string getMode() const {
        return mode;
    }
    long long getCapacity() const { 
        return capacity; 
    }
    double getBaseFare() const { 
        return baseFare; 
    }
    long long getBuyPrice() const { 
        return buyPrice; 
    }
    bool isOwned() const { 
        return owned; 
    }
    void setOwned(bool o) { 
        owned = o; 
    }
    long long getQuantity()  {
        return quantity;
    }
    void setQuantity(long long q) {
        quantity = q < 0 ? 0 : q;
    }
    long long calculateFare(long long distance) const {
        return static_cast<long long>(baseFare + (distance * 1.76));
    }
};



