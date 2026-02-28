#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Создаем окно размером 800x600 пикселей с заголовком "SFML Tutorial - Example 1"
    // SFML 3.0: VideoMode теперь принимает Vector2u
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(800, 600)), 
        "SFML Tutorial - Example 1"
    );
    
    // Устанавливаем ограничение частоты кадров (опционально)
    window.setFramerateLimit(60);
    
    std::cout << "Окно создано! Нажмите ESC или закройте окно для выхода." << std::endl;
    
    // Главный цикл приложения
    while (window.isOpen())
    {
        // Обработка событий
        // SFML 3.0: pollEvent() возвращает std::optional<Event>
        while (auto event = window.pollEvent())
        {
            // Проверяем тип события
            // SFML 3.0: используем is<>() вместо проверки type
            if (event->is<sf::Event::Closed>())
            {
                std::cout << "Событие закрытия окна получено." << std::endl;
                // window.close();
            }
            
            // Обработка нажатия клавиши ESC
            // SFML 3.0: Keyboard::Key теперь enum class
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape)
                {
                    std::cout << "Нажата клавиша ESC." << std::endl;
                    window.close();
                }
            }
        }
        
        // Очистка экрана цветом (темно-синий)
        window.clear(sf::Color(20, 30, 50));
        
        // Здесь можно рисовать объекты
        // Пока просто очищаем экран
        
        // Отображение всего, что было нарисовано
        window.display();
    }
    
    std::cout << "Приложение завершено." << std::endl;
    return 0;
}
