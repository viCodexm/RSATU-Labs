#pragma once
#include "Consts.hpp"
#include "ReactiveRectangle.hpp"

struct ButtonWithText : sf::RectangleShape {
    bool pressed = false;
    sf::Text label; sf::Font font;
    ButtonWithText() {
        this->setFillColor(COLOR_BACKGROUND);
        this->setSize({CELL_WIDTH, CELL_WIDTH / 2});
        this->setOutlineThickness(CELL_OUTLINE);
        this->setOutlineColor(sf::Color::Black);
        this->label.setOutlineColor(sf::Color::Black);
        this->label.setOutlineThickness(2.0);
        this->font.loadFromFile("Matias Webfont.ttf");
        this->label.setFont(font);
        this->label.setLetterSpacing(2.5);
        this->label.setCharacterSize(20);
        this->label.setFillColor(sf::Color::White);
        
    }
    void set(sf::Vector2f position, std::string message) {
        this->setPosition(position);
        this->label.setPosition(this->getPosition().x + 6, this->getPosition().y + 2);
        this->label.setString(message);
    }
    bool onTap(sf::RenderWindow& window) {
        return this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window))
            && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    void logic(sf::RenderWindow& window) {
        pressed |= onTap(window);
        this->setFillColor(
            pressed ? COLOR_BLUE_PRESS : COLOR_BACKGROUND
        );
        if (pressed) sf::sleep(sf::milliseconds(200));
        window.draw(*this);
        window.draw(label);
    }
};

struct WinnerBoard : sf::RectangleShape {
    sf::Text label; sf::Font font; bool draw = false; ButtonWithText retry;
    WinnerBoard() {
        this->retry.set({122, SCREEN_HEIGHT * 0.4 + 100}, "Retry");
        this->setFillColor(COLOR_BASIC_PRESS);
        this->setSize({CELL_WIDTH * 4, CELL_WIDTH * 2.45});
        this->setPosition({32, SCREEN_HEIGHT * 0.4});
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(CELL_OUTLINE);
        this->label.setPosition(this->getPosition().x + 10, this->getPosition().y + 50);
        this->label.setOutlineColor(sf::Color::Black);
        this->label.setOutlineThickness(3.0);
        this->font.loadFromFile("Matias Webfont.ttf");
        this->label.setFont(font);
        this->label.setLetterSpacing(2.5);
        this->label.setCharacterSize(30);
    }
    void set_message(const char* message, sf::Color message_color) {
        this->label.setString(message);
        message_color.a = 255;
        this->label.setColor(message_color);
        this->label.setFillColor(message_color);
        draw = true;
    }
    void logic(sf::RenderWindow& window) {
        if (this->draw) {
            window.draw(*this);
            window.draw(label);
            retry.logic(window);
        }
    }
};

struct GameModeBoard : WinnerBoard {
    ButtonWithText pvp, pve;
    bool draw = true;
    int gamemode = -1;
    GameModeBoard() {
        this->label.setCharacterSize(22);
        this->label.setPosition({55, SCREEN_HEIGHT * 0.4 + 10});
        set_message("Choose game mode", COLOR_RED);
        this->setFillColor(COLOR_BASIC_PRESS);
        this->setSize({CELL_WIDTH * 4, CELL_WIDTH * 2.45});
        this->setPosition({32, SCREEN_HEIGHT * 0.4});
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(CELL_OUTLINE);
        this->pvp.set({122, SCREEN_HEIGHT * 0.4 + 50}, "PvP");
        this->pve.set({122, SCREEN_HEIGHT * 0.4 + 100}, "PvE");
    }
    void logic(sf::RenderWindow& window) {
        if (this->draw) {
            window.draw(*this);
            window.draw(label);
            pvp.logic(window);
            if (pvp.pressed) {gamemode = 1; return;}
            pve.logic(window);
            if (pve.pressed) {gamemode = 2; return;}
        }
    }
};

struct ChooseMoveBoard : WinnerBoard {
    ButtonWithText red, blue;
    bool draw = true;
    int player_color = -1;
    ChooseMoveBoard() {
        this->label.setCharacterSize(22);
        this->label.setPosition({55, SCREEN_HEIGHT * 0.4 + 10});
        set_message("Choose your color", COLOR_RED);
        this->setFillColor(COLOR_BASIC_PRESS);
        this->setSize({CELL_WIDTH * 4, CELL_WIDTH * 2.45});
        this->setPosition({32, SCREEN_HEIGHT * 0.4});
        this->setOutlineColor(sf::Color::Black);
        this->setOutlineThickness(CELL_OUTLINE);
        this->red.set({122, SCREEN_HEIGHT * 0.4 + 50}, "red");
        this->blue.set({122, SCREEN_HEIGHT * 0.4 + 100}, "blue");
    }
    void logic(sf::RenderWindow& window) {
        if (this->draw) {
            window.draw(*this);
            window.draw(label);
            red.logic(window);
            if (red.pressed) {player_color = 1; return;}
            blue.logic(window);
            if (blue.pressed) {player_color = 2; return;}
        }
    }
};