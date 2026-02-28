#include "Button.h"
#include <iostream>

Button::Button(sf::Texture& texture, const std::string& text, 
               const sf::Font& font, unsigned int fontSize)
    : m_state(State::Normal)
    , m_text(font, text, fontSize)  // SFML 3.0: Text(font, string, characterSize)
    , m_font(font)
    , m_normalColor(sf::Color(70, 130, 180))    // Стальной синий
    , m_hoverColor(sf::Color(100, 160, 210))    // Светлее
    , m_pressedColor(sf::Color(50, 100, 150))   // Темнее
{
    // Настройка формы кнопки
    m_shape.setSize(sf::Vector2f(200, 50));
    m_shape.setFillColor(m_normalColor);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2.0f);
    
    // Настройка текста
    m_text.setFillColor(sf::Color::White);
    
    // Центрирование текста (будет обновлено в setPosition)
    updateColor();
}

void Button::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_shape.setPosition(position);
    m_text.setPosition(calculateTextPosition());
}

void Button::setSize(float width, float height)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_text.setPosition(calculateTextPosition());
}

void Button::setBackgroundColor(const sf::Color& color)
{
    m_normalColor = color;
    updateColor();
}

void Button::setHoverColor(const sf::Color& color)
{
    m_hoverColor = color;
    updateColor();
}

void Button::setPressedColor(const sf::Color& color)
{
    m_pressedColor = color;
    updateColor();
}

void Button::setText(const std::string& text)
{
    m_text.setString(text);
    m_text.setPosition(calculateTextPosition());
}

void Button::setOnClick(std::function<void()> callback)
{
    m_onClick = callback;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    // Получаем позицию мыши в координатах окна
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                          static_cast<float>(mousePos.y));
    
    // Проверяем, находится ли мышь над кнопкой
    bool mouseOver = contains(mousePosF);
    
    // Обработка событий мыши
    if (event.is<sf::Event::MouseMoved>())
    {
        if (mouseOver && m_state == State::Normal)
        {
            m_state = State::Hover;
            updateColor();
        }
        else if (!mouseOver && m_state == State::Hover)
        {
            m_state = State::Normal;
            updateColor();
        }
    }
    else if (event.is<sf::Event::MouseButtonPressed>())
    {
        // SFML 3.0: getIf возвращает указатель, а не ссылку
        if (auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseEvent->button == sf::Mouse::Button::Left && mouseOver)
            {
                m_state = State::Pressed;
                updateColor();
            }
        }
    }
    else if (event.is<sf::Event::MouseButtonReleased>())
    {
        // SFML 3.0: getIf возвращает указатель, а не ссылку
        if (auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            if (m_state == State::Pressed && mouseOver)
            {
                // Кнопка была нажата и отпущена над ней - вызываем callback
                if (m_onClick)
                {
                    m_onClick();
                }
            }
            
            if (mouseOver)
            {
                m_state = State::Hover;
            }
            else
            {
                m_state = State::Normal;
            }
            updateColor();
        }
        }
    }
}

void Button::update(const sf::RenderWindow& window)
{
    // Обновление состояния при движении мыши (если окно не в фокусе)
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), 
                          static_cast<float>(mousePos.y));
    
    bool mouseOver = contains(mousePosF);
    
    if (!mouseOver && m_state == State::Hover)
    {
        m_state = State::Normal;
        updateColor();
    }
}

void Button::draw(sf::RenderTarget& target) const
{
    target.draw(m_shape);
    target.draw(m_text);
}

bool Button::contains(const sf::Vector2f& point) const
{
    sf::FloatRect bounds = m_shape.getGlobalBounds();
    return bounds.contains(point);
}

sf::Vector2f Button::getSize() const
{
    return m_shape.getSize();
}

sf::Vector2f Button::getPosition() const
{
    return m_shape.getPosition();
}

void Button::updateColor()
{
    switch (m_state)
    {
        case State::Normal:
            m_shape.setFillColor(m_normalColor);
            break;
        case State::Hover:
            m_shape.setFillColor(m_hoverColor);
            break;
        case State::Pressed:
            m_shape.setFillColor(m_pressedColor);
            break;
    }
}

sf::Vector2f Button::calculateTextPosition() const
{
    sf::FloatRect textBounds = m_text.getLocalBounds();
    sf::Vector2f shapePos = m_shape.getPosition();
    sf::Vector2f shapeSize = m_shape.getSize();
    
    // Центрирование текста
    // SFML 3.0: FloatRect использует поля size и position
    float x = shapePos.x + (shapeSize.x - textBounds.size.x) / 2.0f - textBounds.position.x;
    float y = shapePos.y + (shapeSize.y - textBounds.size.y) / 2.0f - textBounds.position.y;
    
    return sf::Vector2f(x, y);
}
