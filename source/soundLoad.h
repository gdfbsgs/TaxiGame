// Загрузка звука клика мыши
sf::SoundBuffer click;
    if (!click.loadFromFile("sound/click.wav"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(click);

    // Загрузка звука старта игры
    sf::SoundBuffer start;
    if (!start.loadFromFile("sound/start.wav"))
        return -1;
    sf::Sound sound2;
    sound2.setBuffer(start);

    // Загрузка звука остановки/выхода
    sf::SoundBuffer stop;
    if (!stop.loadFromFile("sound/stop.wav"))
        return -1;
    sf::Sound sound3;
    sound3.setBuffer(stop);

