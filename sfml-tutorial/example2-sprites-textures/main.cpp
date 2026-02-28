#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

int main()
{
    // Создаем окно
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(800, 600)), 
        "SFML Tutorial - Example 2: Sprites and Textures"
    );
    window.setFramerateLimit(60);
    
    // Шаг 1: Создание текстуры
    sf::Texture texture;
    
    // Попытка загрузить изображение
    // ВАЖНО: Путь к файлу должен быть правильным!
    // Если изображение не найдено, можно использовать простой цветной прямоугольник
    bool textureLoaded = texture.loadFromFile("resources/cat.png");
    
    if (!textureLoaded)
    {
        std::cout << "Предупреждение: Не удалось загрузить resources/cat.png" << std::endl;
        std::cout << "Создаем текстуру программно..." << std::endl;
        
        // Создаем простую текстуру программно (красный квадрат 64x64)
        // SFML 3.0: используем конструктор Image с размером и цветом
        sf::Image image(sf::Vector2u(64, 64), sf::Color::Red);
        if (!texture.loadFromImage(image))
        {
            std::cerr << "Ошибка: Не удалось создать текстуру из изображения!" << std::endl;
        }
    }
    else
    {
        std::cout << "Текстура успешно загружена!" << std::endl;
        sf::Vector2u textureSize = texture.getSize();
        std::cout << "Размер текстуры: " << textureSize.x << "x" << textureSize.y << std::endl;
    }
    
    // Шаг 2: Создание спрайта
    // SFML 3.0: Конструктор Sprite требует текстуру
    sf::Sprite sprite(texture);
    
    // Шаг 4: Масштабирование (опционально)
    // SFML 3.0: setScale принимает Vector2f
    sf::Vector2u textureSize = texture.getSize();
    
    // Автоматически подбираем масштаб, чтобы спрайт поместился на экране
    // Если изображение слишком большое, уменьшаем масштаб
    float maxWidth = 400.0f;  // Максимальная ширина спрайта на экране
    float maxHeight = 400.0f; // Максимальная высота спрайта на экране
    float scaleX = maxWidth / textureSize.x;
    float scaleY = maxHeight / textureSize.y;
    float initialScale = std::min({scaleX, scaleY, 2.0f}); // Не больше 2x, но не больше чем нужно
    
    sprite.setScale(sf::Vector2f(initialScale, initialScale));
    
    // Шаг 3: Установка позиции спрайта
    // Центрируем спрайт в окне с учетом масштаба
    // SFML 3.0: setPosition принимает Vector2f
    float scaledWidth = textureSize.x * initialScale;
    float scaledHeight = textureSize.y * initialScale;
    float posX = (800.0f - scaledWidth) / 2.0f;
    float posY = (600.0f - scaledHeight) / 2.0f;
    
    // Убеждаемся, что позиция не отрицательная (если спрайт больше экрана)
    posX = std::max(0.0f, posX);
    posY = std::max(0.0f, posY);
    
    sprite.setPosition(sf::Vector2f(posX, posY));
    
    std::cout << "Размер текстуры: " << textureSize.x << "x" << textureSize.y << std::endl;
    std::cout << "Масштаб спрайта: " << initialScale << "x" << std::endl;
    std::cout << "Размер спрайта на экране: " << scaledWidth << "x" << scaledHeight << std::endl;
    std::cout << "Позиция спрайта: (" << posX << ", " << posY << ")" << std::endl;
    
    // Переменные для анимации
    float angle = 0.0f;
    float scale = 2.0f;
    bool growing = true;
    
    std::cout << "Управление:" << std::endl;
    std::cout << "  Стрелки - перемещение спрайта" << std::endl;
    std::cout << "  R - поворот" << std::endl;
    std::cout << "  +/- - масштабирование" << std::endl;
    std::cout << "  ESC - выход" << std::endl;
    
    // Главный цикл
    while (window.isOpen())
    {
        // Обработка событий
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            // Обработка нажатий клавиш
            if (event->is<sf::Event::KeyPressed>())
            {
                // SFML 3.0: используем getIf для получения события
                if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
                {
                    // Перемещение стрелками
                    // SFML 3.0: setPosition принимает Vector2f
                    sf::Vector2f position = sprite.getPosition();
                    
                    if (keyEvent->code == sf::Keyboard::Key::Left)
                        sprite.setPosition(sf::Vector2f(position.x - 10, position.y));
                    if (keyEvent->code == sf::Keyboard::Key::Right)
                        sprite.setPosition(sf::Vector2f(position.x + 10, position.y));
                    if (keyEvent->code == sf::Keyboard::Key::Up)
                        sprite.setPosition(sf::Vector2f(position.x, position.y - 10));
                    if (keyEvent->code == sf::Keyboard::Key::Down)
                        sprite.setPosition(sf::Vector2f(position.x, position.y + 10));
                    
                    // Поворот
                    // SFML 3.0: setRotation принимает Angle, используем функцию sf::degrees()
                    if (keyEvent->code == sf::Keyboard::Key::R)
                    {
                        angle += 15.0f;
                        sprite.setRotation(sf::degrees(angle));
                    }
                    
                    // Масштабирование
                    // SFML 3.0: setScale принимает Vector2f
                    if (keyEvent->code == sf::Keyboard::Key::Equal || 
                        keyEvent->code == sf::Keyboard::Key::Add)
                    {
                        scale += 0.1f;
                        sprite.setScale(sf::Vector2f(scale, scale));
                    }
                    if (keyEvent->code == sf::Keyboard::Key::Hyphen || 
                        keyEvent->code == sf::Keyboard::Key::Subtract)
                    {
                        scale = std::max(0.1f, scale - 0.1f);
                        sprite.setScale(sf::Vector2f(scale, scale));
                    }
                    
                    // Выход
                    if (keyEvent->code == sf::Keyboard::Key::Escape)
                        window.close();
                }
            }
        }
        
        // Автоматическая анимация (пульсация)
        static float time = 0.0f;
        time += 0.02f;
        float pulseScale = 2.0f + 0.3f * std::sin(time);
        // Можно раскомментировать для автоматической пульсации:
        // SFML 3.0: setScale принимает Vector2f
        // sprite.setScale(sf::Vector2f(pulseScale, pulseScale));
        
        // Очистка экрана
        window.clear(sf::Color(30, 30, 50));
        
        // Отрисовка спрайта
        window.draw(sprite);
        
        // Отображение
        window.display();
    }
    
    return 0;
}
