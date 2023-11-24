#pragma once

#include <SFML/Graphics.hpp>
#include "Consts.hpp"

struct Button : sf::RectangleShape {

    bool pressed = false;
    float speed = 0.05;
    int offset = 0;
    void (Button::*logic)(sf::RenderWindow&);


    void standart_logic(sf::RenderWindow& window) {
        pressed = onTap(window);
        this->setFillColor(
            pressed ? COLOR_BASIC_PRESS : COLOR_BASIC
        );
    }
    void jumping_logic(sf::RenderWindow& window) {
        standart_logic(window);
        this->setFillColor(
            pressed ? COLOR_BLUE_PRESS : COLOR_BLUE
        );
    }
    
    bool onTap(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f rectPos = this->getPosition();
        sf::Vector2f rectSize = this->getSize();
        return (mousePos.x >= rectPos.x && mousePos.x <= rectPos.x + rectSize.x &&
                mousePos.y >= rectPos.y && mousePos.y <= rectPos.y + rectSize.y &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left));
    }
    void shake() {
        offset++;
        this->move(0.0f, speed);
        const int border = 100;
        if (offset > border) {
            speed = -speed;
            offset = -border;
        }
    }
};