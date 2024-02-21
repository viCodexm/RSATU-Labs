#pragma once
#include "Consts.hpp"

struct ReactiveRectangle : sf::RectangleShape {

    bool pressed = false;
    bool isGamePiecePlayer = false;
    bool isGamePieceEnemy = false;
    bool hint = false;
    
    void logic(sf::RenderWindow& window, int player_move) {
        pressed |= onTap(window);
        this->setFillColor( this->hint ? COLOR_GREEN :
            isGamePiecePlayer ? player_move ?
                pressed ? COLOR_BLUE_PRESS : COLOR_BLUE
                : COLOR_BLUE
            : isGamePieceEnemy ? !player_move ?
                    pressed ? COLOR_RED_PRESS : COLOR_RED
                    : COLOR_RED
                : pressed ? COLOR_BASIC_PRESS : COLOR_BASIC);
    }
    
    bool onTap(sf::RenderWindow& window) {
        return this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window))
            && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
};