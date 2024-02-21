#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

struct Board {
    std::vector<Button> cells;
    bool can_redistribute = false;

    class Animation {
        sf::Clock startTimestamp;
    public:
        
        void startAnimation() {
            this->startTimestamp.restart();
        }
        
        bool hasAnimationEnded(Button button) {
            return (this->startTimestamp.getElapsedTime().asSeconds() > 1 && button.offset == 0);
        }
    };
    Animation animation;
    
    
    Board(const int n, const int m) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Button cell;
                cell.setFillColor(COLOR_BASIC);
                cell.setSize({CELL_WIDTH, CELL_WIDTH});
                cell.setPosition({50 + (float)CELL_OFFSET * j, 50 + (float)CELL_OFFSET * i});
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(CELL_OUTLINE);
                cells.push_back(cell);
            }
        }
        redistribute();
    }
    
    void redistribute() {
        int idx = 0, jumping_idx = rng() % cells.size();
        for (Button& cell : cells) {
            if (idx == jumping_idx)
                cell.logic = &Button::jumping_logic;
            else cell.logic = &Button::standart_logic;
            idx++;
        }
        this->can_redistribute = false;
    }

    void game_logic(sf::RenderWindow& window) {

        for (Button& cell : cells) {
            (cell.*cell.logic)(window);

            if (cell.logic == &Button::jumping_logic) {

                if (cell.pressed) {
                    animation.startAnimation();

                    while (!animation.hasAnimationEnded(cell)) {
                        cell.shake();
                        sf::sleep(sf::microseconds(300));
                    }
                    if (can_redistribute)
                        redistribute();
                }
            } 
            else if (can_redistribute && cell.pressed) {
                redistribute();
            }
        };
    }

};