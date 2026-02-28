#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

// Класс для создания интерактивных кнопок
class Button
{
public:
    // Конструктор
    // SFML 3.0: Sprite требует текстуру в конструкторе
    Button(sf::Texture& texture, const std::string& text, 
           const sf::Font& font, unsigned int fontSize = 24);
    
    // Установка позиции
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    
    // Установка размера
    void setSize(float width, float height);
    
    // Установка цвета фона
    void setBackgroundColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setPressedColor(const sf::Color& color);
    
    // Установка текста
    void setText(const std::string& text);
    
    // Установка callback функции (вызывается при нажатии)
    void setOnClick(std::function<void()> callback);
    
    // Обработка событий (вызывать в главном цикле)
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    
    // Обновление состояния (вызывать в главном цикле)
    void update(const sf::RenderWindow& window);
    
    // Отрисовка
    void draw(sf::RenderTarget& target) const;
    
    // Проверка, находится ли точка внутри кнопки
    bool contains(const sf::Vector2f& point) const;
    
    // Получение размеров
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

private:
    // Состояния кнопки
    enum class State
    {
        Normal,   // Обычное состояние
        Hover,    // Наведение мыши
        Pressed   // Нажата
    };
    
    State m_state;
    
    // Графические компоненты
    sf::RectangleShape m_shape;      // Форма кнопки
    sf::Text m_text;                 // Текст на кнопке
    sf::Font m_font;                 // Шрифт (копия)
    
    // Цвета для разных состояний
    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Color m_pressedColor;
    
    // Callback функция
    std::function<void()> m_onClick;
    
    // Вспомогательные методы
    void updateColor();
    sf::Vector2f calculateTextPosition() const;
};

#endif // BUTTON_H
