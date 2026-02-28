#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // Создаем окно
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(800, 600)), 
        "SFML Tutorial - Example 3: Buttons"
    );
    window.setFramerateLimit(60);
    
    // Загрузка шрифта
    // SFML не предоставляет встроенных шрифтов, нужно загрузить свой
    // Для примера используем системный шрифт или создаем простую кнопку без текста
    sf::Font font;
    
    // Попытка загрузить шрифт (если есть)
    // На macOS можно использовать системные шрифты:
    // font.loadFromFile("/System/Library/Fonts/Helvetica.ttc");
    // Или скачать бесплатный шрифт (например, с Google Fonts)
    
    // Если шрифт не загружен, создадим кнопку без текста (только форма)
    bool fontLoaded = false;
    
    // Попытка загрузить шрифт из стандартных мест
    // Используем шрифты с поддержкой кириллицы
    std::vector<std::string> fontPaths = {
        "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",  // macOS - поддерживает кириллицу
        "/System/Library/Fonts/Helvetica.ttc",                    // macOS - fallback
        "/Library/Fonts/Arial.ttf",                              // macOS - альтернатива
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",      // Linux
        "resources/font.ttf"                                     // Локальный
    };
    
    for (const auto& path : fontPaths)
    {
        // SFML 3.0: используем openFromFile вместо loadFromFile
        if (font.openFromFile(path))
        {
            fontLoaded = true;
            std::cout << "Шрифт загружен: " << path << std::endl;
            break;
        }
    }
    
    if (!fontLoaded)
    {
        std::cout << "Предупреждение: Шрифт не загружен. Кнопки будут без текста." << std::endl;
        std::cout << "Скачайте бесплатный шрифт с поддержкой кириллицы (например, с Google Fonts)" << std::endl;
        std::cout << "и поместите в resources/font.ttf" << std::endl;
        std::cout << "Рекомендуемые шрифты: Roboto, Open Sans, Noto Sans" << std::endl;
    }
    else
    {
        std::cout << "Примечание: Если видите квадраты вместо текста, шрифт не поддерживает кириллицу." << std::endl;
        std::cout << "Используйте шрифт с поддержкой Unicode (например, Arial Unicode MS или скачайте с Google Fonts)" << std::endl;
    }
    
    // Создаем фиктивную текстуру для кнопки (не используется, но требуется конструктором)
    // SFML 3.0: создаем текстуру через Image, так как create() удален
    sf::Texture dummyTexture;
    sf::Image dummyImage(sf::Vector2u(1, 1), sf::Color::White);
    if (!dummyTexture.loadFromImage(dummyImage))
    {
        std::cerr << "Ошибка: Не удалось создать фиктивную текстуру!" << std::endl;
    }
    
    // Создаем кнопки
    // Используем английский текст по умолчанию для совместимости
    // Если нужна кириллица, используйте шрифт с поддержкой Unicode (например, Arial Unicode MS)
    std::string button1Text = fontLoaded ? "Button 1" : "";
    std::string button2Text = fontLoaded ? "Button 2" : "";
    std::string button3Text = fontLoaded ? "Exit" : "";
    
    // Для использования кириллицы раскомментируйте следующие строки
    // и убедитесь, что загружен шрифт с поддержкой кириллицы
    // button1Text = "Кнопка 1";
    // button2Text = "Кнопка 2";
    // button3Text = "Выход";
    
    Button button1(dummyTexture, button1Text, font, 24);
    Button button2(dummyTexture, button2Text, font, 24);
    Button button3(dummyTexture, button3Text, font, 24);
    
    // Устанавливаем позиции
    button1.setPosition(300, 150);
    button2.setPosition(300, 250);
    button3.setPosition(300, 350);
    
    // Настройка цветов
    button1.setBackgroundColor(sf::Color(70, 130, 180));
    button1.setHoverColor(sf::Color(100, 160, 210));
    button1.setPressedColor(sf::Color(50, 100, 150));
    
    button2.setBackgroundColor(sf::Color(180, 70, 130));
    button2.setHoverColor(sf::Color(210, 100, 160));
    button2.setPressedColor(sf::Color(150, 50, 100));
    
    button3.setBackgroundColor(sf::Color(180, 70, 70));
    button3.setHoverColor(sf::Color(210, 100, 100));
    button3.setPressedColor(sf::Color(150, 50, 50));
    
    // Устанавливаем callback функции
    int clickCount1 = 0;
    int clickCount2 = 0;
    
    button1.setOnClick([&clickCount1]() {
        clickCount1++;
        std::cout << "Кнопка 1 нажата! Счетчик: " << clickCount1 << std::endl;
    });
    
    button2.setOnClick([&clickCount2]() {
        clickCount2++;
        std::cout << "Кнопка 2 нажата! Счетчик: " << clickCount2 << std::endl;
    });
    
    button3.setOnClick([&window]() {
        std::cout << "Выход из приложения..." << std::endl;
        window.close();
    });
    
    std::cout << "Интерактивные кнопки готовы!" << std::endl;
    std::cout << "Наведите мышь на кнопки и нажмите на них." << std::endl;
    
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
            
            // Передаем события кнопкам (разыменовываем optional)
            sf::Event ev = *event;
            button1.handleEvent(ev, window);
            button2.handleEvent(ev, window);
            button3.handleEvent(ev, window);
            
            // Обработка ESC
            if (event->is<sf::Event::KeyPressed>())
            {
                auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }
        
        // Обновление кнопок (для обработки движения мыши)
        button1.update(window);
        button2.update(window);
        button3.update(window);
        
        // Очистка экрана
        window.clear(sf::Color(40, 40, 60));
        
        // Отрисовка кнопок
        button1.draw(window);
        button2.draw(window);
        button3.draw(window);
        
        // Отображение
        window.display();
    }
    
    std::cout << "Приложение завершено." << std::endl;
    std::cout << "Кнопка 1 была нажата " << clickCount1 << " раз(а)." << std::endl;
    std::cout << "Кнопка 2 была нажата " << clickCount2 << " раз(а)." << std::endl;
    
    return 0;
}
